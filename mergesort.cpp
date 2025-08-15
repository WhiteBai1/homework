#include <ctime>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

vector<float> arr;
auto n = 0;
vector<float> tmp;

template <typename randomIt, typename compare>
void mergesort(randomIt l, randomIt r, compare comp) {
  /*if (l >= r)
    return;*/
  auto size = distance(l, r);
  if (size <= 1)
    return;

  randomIt mid = l + (r - l) / 2;
  mergesort(l, mid, comp);
  mergesort(mid, r, comp);

  auto left = l, right = mid;
  auto tmpIt = tmp.begin();

  while (left != mid && right != r) {
    *tmpIt++ = comp(*left, *right) ? *left++ : *right++;
  }

  tmpIt = std::copy(left, mid, tmpIt);
  std::copy(right, r, tmpIt);
  std::copy(tmp.begin(), tmp.begin() + size, l);

  /*int i = l, j = mid + 1, k = l;
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
}*/
  return;
}

template <typename randomIt> void mergesort(randomIt l, randomIt r) {
  mergesort(l, r, std::less<>());
}

template <typename T> void inputArray(vector<T> &arr) {
  T num;
  while (cin.peek() != '\n') {
    std::cin >> num;
    arr.push_back(num);
    n++;
  }
}

int main() {
  // cin >> n;

  /*for (int i = 0; i < n; i++)
    cin >> arr[i];*/
  inputArray(arr);

  auto first = arr.begin();
  auto last = arr.end();
  auto size = distance(first, last);
  tmp.resize(size);

  mergesort(first, last);

  for (int i = 0; i < n; i++)
    cout << arr[i] << " ";
  return 0;
}
