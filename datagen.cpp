#include <ctime>
#include <fstream>
#include <iostream>
#include <random>

void datagenerate(int n) {
  std::mt19937 rnd(std::time(nullptr));

  std::ofstream outfile("result.txt");
  if (!outfile.is_open()) {
    std::cerr << "fail to open file" << '\n';
    return;
  }

  // int n = 1000000;

  std::cin >> n;
  outfile << n << '\n';
  for (int i = 1; i <= n; i++) {
    outfile << rnd() % 1000 << " ";
  }
  outfile << '\n';
  outfile.close();
  return;
}

/*int main() {
  int n;
  std::cin >> n;
  datagenerate(n);
  return 0;
}*/