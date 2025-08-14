#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

int main() {
  std::mt19937 rnd(std::time(nullptr));

  std::ofstream outfile("result.txt");
  if (!outfile.is_open()) {
    std::cerr << "fail to open file" << '\n';
    return 1;
  }

  int n = 1000000;
  outfile << n << '\n';
  for (int i = 1; i <= n; i++) {
    outfile << rnd() % 1000 << " ";
  }
  outfile << '\n';
  outfile.close();
  return 0;
}