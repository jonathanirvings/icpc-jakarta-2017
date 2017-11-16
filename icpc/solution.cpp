// Solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  vector<int> testcases(M);
  for (int i = 0; i < M; ++i) {
    scanf("%d", &testcases[i]);
  }
  pair<int, int> winning_team = make_pair(-1, 1);
  for (int i = 0; i < N; ++i) {
    int solves = 0;
    for (int j = 0; j < M; ++j) {
      int tc_solved;
      scanf("%d", &tc_solved);
      if (tc_solved == testcases[j]) {
        ++solves;
      }
    }
    if (solves > winning_team.first) {
      winning_team = make_pair(solves, i);
    }
  }
  printf("%d\n", winning_team.second + 1);
}
