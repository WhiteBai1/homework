#include <chrono>
#include <fstream>
#include <iostream>
// #include <vector>
using namespace std;

const int MAXN = 1000000;

int arr[MAXN];

int partition(int *a, int l, int r);
void quicksort(int *a, int l, int r);

int main() {

  /*std::ifstream infile("result3.txt");
  if (!infile.is_open()) {
    std::cerr << "Failed to open result1 file!" << '\n';
    return 1;
  }*/
  // cout << "open" << '\n';

  // cin >> n;

  // vector<int>arr;
  // int num;
  // n=0;
  /**while(cin.peek()!='\n'){
      cin >> num;
      arr.push_back(num);
      n++;
  }**/
  // for (int i = 0; i < n; i++)
  // cin >> arr[i];

  // infile.close();

  // cout << "write" << '\n';

  /*std::ofstream outfile("result2.txt");
  if (!outfile.is_open()) {
    std::cerr << "fail to open result2 file" << '\n';
    return 1;
  }*/

  // quicksort(arr, 0, n - 1);

  // cout << "order" << '\n';

  /*for (int i = n - 1; i >= 0; i--)
    cout << arr[i] << " ";
  cout << '\n';
  // outfile << arr[i] << " ";
  // outfile << '\n';
  // outfile.close();*/

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  const int runs = 100;
  double totalTime = 0;

  for (int i = 0; i < runs; i++) {
    int ret = system("./datagen");
    std::ifstream infile("result.txt");
    if (!infile) {
      cerr << "错误: 无法打开 result.txt (run " << runs << ")\n";
      return 1;
    }
    int n;
    infile >> n;

    for (int i = 0; i < n; i++)
      infile >> arr[i];
    infile.close();
    auto start = chrono::high_resolution_clock::now();
    quicksort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    totalTime += chrono::duration<double>(end - start).count();
  }

  double averageTime = totalTime / runs;
  cout << averageTime << '\n';
  return 0;
}

void quicksort(int *a, int l, int r) {
  if (l >= r)
    return;
  int q = partition(a, l, r);
  quicksort(a, l, q - 1);
  quicksort(a, q + 1, r);
}

int partition(int *a, int l, int r) {
  int x = a[r];
  int i = l - 1;
  for (int j = l; j <= r - 1; j++) {
    if (a[j] >= x) {
      i++;
      if (j != i) {
        std::swap(a[i], a[j]);
      }
    }
  }
  i++;
  std::swap(a[i], a[r]);
  return i;
}