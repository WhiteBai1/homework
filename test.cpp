#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

void quicksort(std::vector<float> &a);
void mergesort(std::vector<float> &a);
void heapsort(std::vector<float> &a);

// quicksort
int partition(std::vector<float> &a, int l, int r) {
  auto x = a[r];
  int i = l - 1;
  for (int j = l; j <= r - 1; j++) {
    if (a[j] <= x) {
      i++;
      if (j != i) {
        std::swap(a[i], a[j]);
      }
    }
  }
  i++;
  std::swap(a[i], a[r]);
  return i;
}

void qsort(std::vector<float> &a, int l, int r) {
  if (l >= r)
    return;
  int q = partition(a, l, r);
  qsort(a, l, q - 1);
  qsort(a, q + 1, r);
}

void quicksort(std::vector<float> &a) {
  int n = a.size();
  qsort(a, 0, n - 1);
  return;
}

// mergesort
void msort(std::vector<float> &a, int l, int r, std::vector<float> &tmp) {
  if (l >= r)
    return;

  int mid = l + (r - l) / 2;
  msort(a, l, mid, tmp);
  msort(a, mid + 1, r, tmp);

  int i = l, j = mid + 1, k = l;
  for (; i <= mid && j <= r;) {
    if (a[i] <= a[j]) {
      tmp[k] = a[i];
      i++;
    } else {
      tmp[k] = a[j];
      j++;
    }
    k++;
  }

  if (i <= mid) {
    while (i <= mid) {
      tmp[k] = a[i];
      k++;
      i++;
    }
  } else {
    while (j <= r) {
      tmp[k] = a[j];
      k++, j++;
    }
  }

  k = l;
  while (k <= r) {
    a[k] = tmp[k];
    k++;
  }
  return;
}

void mergesort(std::vector<float> &a) {
  std::vector<float> tmp;
  int n = a.size();
  tmp.resize(n);
  msort(a, 0, n - 1, tmp);
  tmp.reserve(n);
  return;
}

// heapsort
void maxheapfiy(std::vector<float> &a, int i, int len) {
  int l = 2 * i, r = l + 1;
  int smallest = i;
  while (r <= len - 1) {
    if (l <= len - 1 && a[smallest] > a[l])
      smallest = l;
    if (r <= len - 1 && a[smallest] > a[r])
      smallest = r;
    if (smallest != i) {
      std::swap(a[i], a[smallest]);
      i = smallest;
      l = 2 * i;
      r = l + 1;
      // maxheapfiy(a, largest, len);
    } else
      return;
  }
  return;
}
void buildMaxHeap(std::vector<float> &a, int n) {
  for (int i = n / 2 + 1; i >= 0; i--) {
    maxheapfiy(a, i, n);
  }
}

void heapsort(std::vector<float> &a) {
  int n = a.size();
  buildMaxHeap(a, n);
  for (int i = n - 1; i >= 1; i--) {
    std::swap(a[i], a[0]);
    maxheapfiy(a, 0, i);
  }
  return;
}

std::vector<float> randomdata(int scale) {
  std::mt19937 rnd(std::time(nullptr));
  std::vector<float> arr;
  arr.resize(scale);
  for (int i = 0; i < scale; i++) {
    arr[i] = rnd() % 1000;
  }
  return arr;
}

std::vector<float> sortdata(int scale) {
  std::vector<float> arr = randomdata(scale);
  std::sort(arr.begin(), arr.end());
  return arr;
}

std::vector<float> reversedata(int scale) {
  std::vector<float> arr = randomdata(scale);
  std::sort(arr.begin(), arr.end(), std::greater<float>());
  return arr;
}

using duration = std::chrono::duration<double, std::milli>;
duration test(void (*sort_func)(std::vector<float> &),
              std::function<std::vector<float>(int)> data_func, int scale,
              int repeat_times) {
  auto total_time = duration(0);
  for (int i = 0; i < repeat_times; i++) {
    std::vector<float> arr = data_func(scale);
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(arr);
    auto end = std::chrono::high_resolution_clock::now();
    total_time += std::chrono::duration_cast<duration>(end - start);
  }
  return total_time / repeat_times;
}

std::function<std::vector<float>(int)>
data_func_input(const std::string &data_func) {
  if (data_func == "randomdata")
    return &randomdata;
  else if (data_func == "sortdata")
    return &sortdata;
  else if (data_func == "reversedata")
    return &reversedata;
  else
    return nullptr;
}

int main(int argc, char *argv[]) {
  std::cout << "enter sort_func data_func scale repeat_times in sequence"
            << '\n';
  if (argc < 5) {
    std::cout << "input error" << '\n';
  }

  std::string sort_func = argv[1];
  std::string data_func = argv[2];
  int scale = std::stoi(argv[3]);
  int repeat_times = std::stoi(argv[4]);

  auto data_f = data_func_input(data_func);
  if (data_f == nullptr) {
    std::cout << "data_func input error" << '\n';
    return 1;
  }

  duration result;
  if (sort_func == "mergesort") {
    result = test(mergesort, data_f, scale, repeat_times);
  } else if (sort_func == "heapsort") {
    result = test(heapsort, data_f, scale, repeat_times);
  } else if (sort_func == "quicksort") {
    result = test(quicksort, data_f, scale, repeat_times);
  } else {
    std::cout << "sort_func input error" << '\n';
    return 1;
  }

  std::cout << result.count() << "ms" << '\n';
  return 0;
}