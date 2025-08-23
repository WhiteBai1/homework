#pragma once

// this is an inplace-sort function
#include <ranges>
#include <type_traits>
namespace my_sorter {
void inplace_sort(std::ranges::random_access_range auto &arr, auto const &&cmp)
  requires std::is_invocable_r_v<bool, decltype(cmp), decltype(arr[0]),
                                 decltype(arr[1])>
{
  // now let's just use bubble sort as a showcase
  bool sorted = true;
  do {
    sorted = true;
    for (size_t i = 1; i < std::ranges::size(arr); ++i) {
      if (!cmp(arr[i - 1], arr[i]) && cmp(arr[i], arr[i - 1])) {
        // original order  is not sorted, and swap can make it sorted
        std::swap(arr[i - 1], arr[i]);
        sorted = false;
      }
    }
  } while (!sorted);
}

// function overload for default cmp
void inplace_sort(std::ranges::random_access_range auto &arr)
    // we would require the elements of the range to be comparable
  requires requires(decltype(arr) &fake_arr) {
    { fake_arr[0] < fake_arr[1] } -> std::same_as<bool>;
  }
{
  inplace_sort(std::forward<decltype(arr)>(arr),
               [](auto &a, auto &b) { return a < b; });
}
} // namespace my_sorter