// Second solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

int MOD = 1e9 + 7;

void modulo(int &x) {
  if (x < 0) {
    x += MOD;
  }
  if (x >= MOD) {
    x -= MOD;
  }
}

int main() {
  int R, C;
  scanf("%d %d", &R, &C);
  vector<string> data(R);
  vector<int> smallest_bit(1 << R, 0);
  vector<vector<char>> sum(1 << R, vector<char>(C, 0));
  for (int bit = 1; bit < (1 << R); ++bit) {
    for (int i = 0; i < R; ++i) {
      if (bit & (1 << i)) {
        smallest_bit[bit] = i;
        break;
      }
    }
  }
  for (int i = 0; i < R; ++i) {
    cin >> data[i];
  }
  for (int j = 0; j < C; ++j) {
    sum[0][j] = 0;
    for (int i = 0; i < R; ++i) {
      if (data[i][j] == '.') {
        sum[0][j] = sum[0][j] + 1;
      }
    }
  }
  for (int bit = 1; bit < (1 << R); ++bit) {
    for (int j = 0; j < C; ++j) {
      int smallest = smallest_bit[bit];
      if (data[smallest][j] == 'v') {
        sum[bit][j] = sum[bit ^ (1 << smallest)][j];
      } else {
        sum[bit][j] = sum[bit ^ (1 << smallest)][j] - 1;
      }
    }
  }
  int answer = 0;
  for (int bit = 0; bit < (1 << R); ++bit) {
    if (C > 1) {
      int a = 1;
      int b = ((1 << sum[bit][0]) - 1);
      for (int j = 1; j < C; ++j) {
        int c = (long long)(a + b) * ((1 << sum[bit][j]) - 1) % MOD;
        a = b;
        b = c;
      }
      int c = a + b;
      modulo(c);
      if (__builtin_popcount(bit) & 1) {
        answer -= c;
      } else {
        answer += c;
      }
      modulo(answer);
    } else {
      int c = 1 << sum[bit][0];
      if (__builtin_popcount(bit) & 1) {
        answer -= c;
      } else {
        answer += c;
      }
      modulo(answer);
    }
  }
  printf("%d\n", answer);
}
