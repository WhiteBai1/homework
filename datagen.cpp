#include <ctime>
#include <iostream>
#include <random>

int main() {
  std::mt19937 rnd(std::time(nullptr));

  int n = rnd() % 20;
  std::cout << n << std::endl;
  for (int i = 1; i <= n; i++) {
    std::cout << rnd() % 100 << " ";
  }
  std::cout << '\n';
  return 0;
}