#include <csignal>
#include <iostream>
using namespace std;

int n;
void maxheapfiy(int *a, int i, int len);
void buildMaxHeap(int *a);
void heapsort(int *a);

int main() {
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++)
    cin >> arr[i];

  heapsort(arr);

  for (int i = n - 1; i >= 0; i--)
    cout << arr[i] << " ";
  return 0;
}

void buildMaxHeap(int *a) {
  for (int i = n / 2; i >= 0; i--) {
    maxheapfiy(a, i, n);
  }
}

void maxheapfiy(int *a, int i, int len) {
  int l = 2 * i, r = l + 1;
  int largest = i;
  if (l <= len - 1 && a[largest] < a[l])
    largest = l;
  if (r <= len - 1 && a[largest] < a[r])
    largest = r;
  if (largest != i) {
    int tmp = a[i];
    a[i] = a[largest];
    a[largest] = tmp;
    maxheapfiy(a, largest, len);
  }
  return;
}

void heapsort(int *a) {
  buildMaxHeap(a);
  for (int i = n - 1; i >= 1; i--) {
    int tmp = a[i];
    a[i] = a[0];
    a[0] = tmp;
    maxheapfiy(a, 0, i);
  }
}