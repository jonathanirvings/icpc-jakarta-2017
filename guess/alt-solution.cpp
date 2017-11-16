// Second solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

int main() {
  long long N;
  int K;
  string S;
  cin >> N >> K;
  cin >> S;
  vector<long long> answer;
  if (S[S.size() - 1] == '=') {
    if (N < S.size()) {
      answer = {-1};
    } else {
      long long now_length = 1;
      vector<long long> additional_length;
      for (int i = S.size() - 2; i >= 0; --i) {
        if (now_length >= N) {
          additional_length.push_back(1);
        } else {
          if (S[i] == '<') {
            additional_length.push_back(now_length + 1);
          } else {
            additional_length.push_back(now_length);
          }
        }
        now_length += additional_length.back();
      }
      if (now_length < N) {
        answer = {-1};
      } else {
        for (int i = additional_length.size() - 1;
             i >= 0 && now_length > N;
             --i) {
          long long can_reduce = additional_length[i] - 1;
          if (can_reduce >= now_length - N) {
            additional_length[i] -= (now_length - N);
            now_length = N;
          } else {
            additional_length[i] -= can_reduce;
            now_length -= can_reduce;
          }
        }
        long long now_length = 1;
        vector<long long> answer_relative_to_x = {0};
        pair<long long, long long> range_relative_to_x = make_pair(0, 0);
        for (int i = S.size() - 2; i >= 0; --i) {
          if (S[i] == '<') {
            answer_relative_to_x.push_back(range_relative_to_x.second + 1);
            range_relative_to_x.second += additional_length[S.size() - 2 - i];
          } else {
            answer_relative_to_x.push_back(range_relative_to_x.first - 1);
            range_relative_to_x.first -= additional_length[S.size() - 2 - i];
          }
        }
        long long x = N - range_relative_to_x.second;
        for (int i = answer_relative_to_x.size() - 1; i >= 0; --i) {
          answer.push_back(x + answer_relative_to_x[i]);
        }
      }
    }
  } else {
    if (K >= N) {
      answer = {-1};
    } else {
      long long L = 1;
      long long R = N;
      for (int i = 0; i < K; ++i) {
        if (S[i] == '>') {
          answer.push_back(L++);
        } else {
          answer.push_back(R--);
        }
      }
    }
  }
  for (int i = 0; i < answer.size(); ++i) {
    printf("%lld%c", answer[i], "\n "[i + 1 < answer.size() ? 1 : 0]);
  }
}
