// Solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K, T;
  scanf("%d %d %d", &N, &K, &T);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }
  sort(A.begin(), A.end());
  A.push_back(A[0] - 1);
  A.push_back(A[N - 1] + 1);
  sort(A.begin(), A.end());
  int answer_left = 0;
  int answer_right = 0;
  while (A[answer_right + K] == A[answer_right + K + 1]) {
    ++answer_right;
  }
  while (A[K - answer_left] == A[K - answer_left - 1]) {
    ++answer_left;
  }
  int answer = INT_MAX;
  if (A[K + answer_right + 1] <= T) {
    answer = min(answer, answer_right);
  }
  if (answer_right == 0) {
    answer = min(answer, answer_right); 
  }
  if (A[K - answer_left - 1] >= 0) {
    answer = min(answer, answer_left + 1);
  }
  printf("%d\n", answer == INT_MAX ? -1 : answer);
}
