#include <fstream>
#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::ifstream infile("result2.txt");

  bool order = true;
  bool reverse = true;

  int x;
  infile >> x;

  int y;
  while (infile >> y) {
    if (x < y) {
      // std::cout << x << ' ' << y << '\n';
      reverse = false;
      break;
    }
    x = y;
  }

  infile.clear();
  infile.seekg(0);
  infile >> x;

  while (infile >> y) {
    if (x > y) {
      order = false;
      break;
    }
  }

  if (reverse)
    std::cout << "reverse" << '\n';
  else if (order)
    std::cout << "order" << '\n';
  else
    std::cout << "F" << '\n';
  infile.close();
  return 0;
}