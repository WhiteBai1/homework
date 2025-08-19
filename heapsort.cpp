#include <chrono>
#include <csignal>
#include <fstream>
#include <iostream>
#include <utility>
using namespace std;

int arr[1000000];
void maxheapfiy(int *a, int i, int len);
void buildMaxHeap(int *a, int n);
void heapsort(int *a, int n);

int main() {
  /*ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;

  for (int i = 0; i < n; i++)
    cin >> arr[i];

  heapsort(arr);

  for (int i = n - 1; i >= 0; i--)
    cout << arr[i] << " ";*/
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int runs = 100;
  double totalTime = 0;

  for (int i = 0; i < runs; i++) {
    int ret = system("./datagen");
    std::ifstream infile("result.txt");
    if (!infile) {
      cerr << "错误: 无法打开 result.txt (run " << runs << ")\n";
      return 1;
    }
    int n;
    infile >> n;

    for (int i = 0; i < n; i++)
      infile >> arr[i];
    infile.close();
    auto start = chrono::high_resolution_clock::now();
    heapsort(arr, n);
    auto end = chrono::high_resolution_clock::now();
    totalTime += chrono::duration<double>(end - start).count();
  }

  double averageTime = totalTime / runs;
  cout << averageTime << '\n';
  return 0;
}

void buildMaxHeap(int *a, int n) {
  for (int i = n / 2 + 1; i >= 0; i--) {
    maxheapfiy(a, i, n);
  }
}

void maxheapfiy(int *a, int i, int len) {
  int l = 2 * i, r = l + 1;
  int largest = i;
  while (r <= len - 1) {
    if (l <= len - 1 && a[largest] < a[l])
      largest = l;
    if (r <= len - 1 && a[largest] < a[r])
      largest = r;
    if (largest != i) {
      std::swap(a[i], a[largest]);
      i = largest;
      l = 2 * i;
      r = l + 1;
      // maxheapfiy(a, largest, len);
    } else
      return;
  }
  return;
}

void heapsort(int *a, int n) {
  buildMaxHeap(a, n);
  for (int i = n - 1; i >= 1; i--) {
    std::swap(a[i], a[0]);
    maxheapfiy(a, 0, i);
  }
}