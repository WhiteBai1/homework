#include <iostream>
using namespace std;

float arr[1000000];
int n;
float tmp[1000000];

template <typename T> void mergesort(T *a, int l, int r) {
  if (l >= r)
    return;

  int mid = l + (r - l) / 2;
  mergesort(a, l, mid);
  mergesort(a, mid + 1, r);

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

template <typename T> void inputArray(T arr[], int n) {
  for (int i = 0; i < n; i++)
    std::cin >> arr[i];
}

int main() {
  cin >> n;

  /*for (int i = 0; i < n; i++)
    cin >> arr[i];*/
  inputArray(arr, n);

  mergesort(arr, 0, n - 1);

  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  return 0;
}
