#include <iostream>
#include <vector>

int main() {
  std::vector<int> arr;
  int x;
  std::cin >> x;

  int y;
  while (std::cin >> y) {
    if (x < y) {
      std::cout << 'F' << std::endl;
      return 0;
    }
    x = y;
  }

  std::cout << 'T' << std::endl;
  return 0;
}