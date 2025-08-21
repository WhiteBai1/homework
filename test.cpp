#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

std::vector<float> arr;
std::vector<float> tmp;

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
void msort(std::vector<float> &a, int l, int r) {
  if (l >= r)
    return;

  int mid = l + (r - l) / 2;
  msort(a, l, mid);
  msort(a, mid + 1, r);

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
  int n = a.size();
  tmp.resize(n);
  msort(a, 0, n - 1);
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

void randomdata(int scale) {
  std::mt19937 rnd(std::time(nullptr));

  arr.resize(scale);
  for (int i = 0; i < scale; i++) {
    arr[i] = rnd() % 1000;
  }
  return;
}

void sortdata(int scale) {
  randomdata(scale);
  std::sort(arr.begin(), arr.end());
}

void reversedata(int scale) {
  randomdata(scale);
  std::sort(arr.begin(), arr.end(), std::greater<float>());
}

using duration = std::chrono::duration<double, std::milli>;
duration test(void (*sort_func)(std::vector<float> &), void (*data_func)(int),
              int scale, int repeat_times) {
  auto total_time = duration(0);
  for (int i = 0; i < repeat_times; i++) {
    data_func(scale);
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(arr);
    auto end = std::chrono::high_resolution_clock::now();
    total_time += std::chrono::duration_cast<duration>(end - start);
  }
  return total_time / repeat_times;
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

  duration result;
  if (sort_func == "mergesort") {
    if (data_func == "randomdata")
      result = test(mergesort, randomdata, scale, repeat_times);
    else if (data_func == "sortdata")
      result = test(mergesort, sortdata, scale, repeat_times);
    else if (data_func == "reversedata")
      result = test(mergesort, reversedata, scale, repeat_times);
    else {
      std::cout << "data_func input error" << '\n';
      return 1;
    }
  } else if (sort_func == "heapsort") {
    if (data_func == "randomdata")
      result = test(heapsort, randomdata, scale, repeat_times);
    else if (data_func == "sortdata")
      result = test(heapsort, sortdata, scale, repeat_times);
    else if (data_func == "reversedata")
      result = test(heapsort, reversedata, scale, repeat_times);
    else {
      std::cout << "data_func input error" << '\n';
      return 1;
    }
  } else if (sort_func == "quicksort") {
    if (data_func == "randomdata")
      result = test(quicksort, randomdata, scale, repeat_times);
    else if (data_func == "sortdata")
      result = test(quicksort, sortdata, scale, repeat_times);
    else if (data_func == "reversedata")
      result = test(quicksort, reversedata, scale, repeat_times);
    else {
      std::cout << "data_func input error" << '\n';
      return 1;
    }
  } else {
    std::cout << "sort_func input error" << '\n';
    return 1;
  }

  std::cout << result.count() << "ms" << '\n';
  return 0;
}