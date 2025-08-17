#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
using namespace std;

vector<int> arr;
int n;

template <typename iterator> auto partition(iterator l, iterator r) {
  auto left = l, smaller = l;
  auto index = *(r - 1);
  for (; left != r - 1; left++) {
    if (*left <= index) {
      if (left != smaller)
        swap(*smaller, *left);
      smaller++;
    }
  }

  swap(*smaller, *(r - 1));
  return smaller;
}

template <typename iterator>
auto kthquicksort(iterator l, iterator r, int kth) {
  auto size = distance(l, r);
  if (l == r)
    return l;
  auto q = partition(l, r);
  auto leftsize = distance(l, q);
  // cout << leftsize << '\n';
  if (kth < leftsize) {
    // cout << "left" << '\n';
    return kthquicksort(l, q, kth);
  }

  else if (leftsize == kth) {
    // cout << "now" << '\n';
    return q;
  }

  else {
    // cout << "right" << '\n';
    kth = kth - leftsize - 1;
    return kthquicksort(q + 1, r, kth);
  }
}

int main() {
  cin >> n;
  arr.reserve(n);
  int kth;
  cin >> kth;

  int num;
  for (int i = 0; i < n; i++) {
    cin >> num;
    arr.push_back(num);
  }

  auto l = arr.begin();
  auto r = arr.end();

  auto ans = kthquicksort(l, r, kth);

  cout << *ans << '\n';
  return 0;
}