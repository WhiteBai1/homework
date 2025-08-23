#include "sorter.hpp"
#include <cstdio>
#include <print>
#include <vector>

struct BadStruct {
  int x;
};
struct GoodStruct {
  int x;
  auto operator<(GoodStruct const &another) const noexcept -> bool {
    return x < another.x;
  }
};

struct Unmovable {
  int x;
  Unmovable() : x() {} // default constructor
  Unmovable(int _x) : x(_x) {}
  Unmovable(Unmovable const &) = delete;
  Unmovable(Unmovable &&) = delete;
  auto &operator=(Unmovable const &) = delete;
  auto &operator=(Unmovable &&) = delete;
};

int main() {
  int n;
  std::vector<int> arr;
  scanf("%d", &n);
  arr.reserve(n);
  for (int i = 0; i < n; ++i) {
    int x;
    scanf("%d", &x);
    arr.emplace_back(x);
  }

  // Default param, normally sorted
  my_sorter::inplace_sort(arr);
  std::println("length: {}", arr.size());
  std::println("Ordered:");
  for (auto const x : arr) {
    std::print("{} ", x);
  }
  // line end
  std::putchar('\n');

  my_sorter::inplace_sort(arr,
                          [](auto const &a, auto const &b) { return a > b; });
  std::println("Reverse  Ordered:");
  for (auto const x : arr) {
    std::print("{} ", x);
  }
  // line end
  std::putchar('\n');

  my_sorter::inplace_sort(arr, [](auto const &a, auto const &b) {
    // all odds should be treated as smaller than even
    bool a_odd = a & 1;
    bool b_odd = b & 1;
    // both odd or both even, just normal compare
    if (!(a_odd ^ b_odd)) {
      return a < b;
    } else if (a_odd) {
      return true;
    }
    return false;
  });
  std::println("Odd Even Ordered:");
  for (auto const x : arr) {
    std::print("{} ", x);
  }
  // line end
  std::putchar('\n');

  // convert to double
  std::vector<double> darr{arr.begin(), arr.end()};
  my_sorter::inplace_sort(darr);
  std::println("Double  Ordered:");
  for (auto const x : darr) {
    std::print("{:.2f} ", x);
  }
  // line end
  std::putchar('\n');

  std::vector<BadStruct> bad{};
  for (auto const &x : arr) {
    bad.emplace_back(x);
  }
  // uncomment me to see error log
  // my_sorter::inplace_sort(bad);
  // however, we can pass custom compare function to sort it
  my_sorter::inplace_sort(
      bad, [](BadStruct const &a, BadStruct const &b) { return a.x < b.x; });

  std::vector<GoodStruct> good{};
  for (auto const &x : arr) {
    good.emplace_back(x);
  }
  my_sorter::inplace_sort(good);
  std::println("Good Ordered:");
  for (auto const g : good) {
    std::print("{} ", g.x);
  }
  // line end
  std::putchar('\n');

  // unmovable object cannot fit into vector, heck, but we can construct them
  // all at once
  auto *ptr = new Unmovable[n];
  size_t ptr_offset = 0;
  for (auto const &x : arr) {
    ptr[ptr_offset++].x = x;
  }
  // uncomment me to see it doesn't satisfy swap constraint
  //   my_sorter::inplace_sort(
  //       std::span<Unmovable>{ptr, ptr + ptr_offset},
  //       [](Unmovable const &a, Unmovable const &b) { return a.x < b.x; });
  delete[] ptr;
}