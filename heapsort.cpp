#include <csignal>
#include <iostream>
#include <utility>
using namespace std;

int arr[100];
int n;
void maxheapfiy(int *a, int i, int len);
void buildMaxHeap(int *a);
void heapsort(int *a);

int main() {
  cin >> n;

  for (int i = 0; i < n; i++)
    cin >> arr[i];

  heapsort(arr);

  for (int i = n - 1; i >= 0; i--)
    cout << arr[i] << " ";
  return 0;
}

void buildMaxHeap(int *a) {
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

void heapsort(int *a) {
  buildMaxHeap(a);
  for (int i = n - 1; i >= 1; i--) {
    std::swap(a[i], a[0]);
    maxheapfiy(a, 0, i);
  }
}