#include "datagen.hpp"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

extern void datagenerate(int n);
using namespace std;

int arr[1000000];
void mergesort(int *a, int l, int r);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int runs = 100;
  double totalTime = 0;

  vector<int> data_sizes;
  int scale;
  while (cin >> scale) {
    data_sizes.push_back(scale);
  }

  int size = data_sizes.size();

  for (int datatest = 0; datatest < size; datatest++) {
    int scale = data_sizes[datatest];
    datagenerate(scale);
    totalTime = 0;
    for (int i = 0; i < runs; i++) {
      // int ret = system("./datagen");
      std::ifstream infile("result.txt");
      if (!infile) {
        cerr << "错误: 无法打开 result.txt (run " << runs << ")\n";
        return 1;
      }
      int n;
      infile >> n;

      for (int j = 0; j < n; j++)
        infile >> arr[j];
      infile.close();
      auto start = chrono::high_resolution_clock::now();
      mergesort(arr, 0, n - 1);
      auto end = chrono::high_resolution_clock::now();
      totalTime += chrono::duration<double>(end - start).count();
    }

    double averageTime = totalTime / runs;
    /*for (int i = 0; i < n; i++)
      cout << arr[i] << " ";*/
    cout << averageTime << '\n';
  }
  return 0;
}

int tmp[1000000];

void mergesort(int *a, int l, int r) {
  if (l >= r)
    return;

  int mid = l + (r - l) / 2;
  mergesort(a, l, mid);
  mergesort(a, mid + 1, r);

  int i = l, j = mid + 1, k = l;
  for (; i <= mid && j <= r;) {
    if (a[i] >= a[j]) {
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
      k++;
      j++;
    }
  }

  k = l;
  while (k <= r) {
    a[k] = tmp[k];
    k++;
  }
  return;
}