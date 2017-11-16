// Solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

string s, t;
vector<vector<int>> dp;

int f(int now_s, int now_t) {
  if (now_t == t.size()) {
    return 0;
  }
  if (s.size() - now_s < t.size() - now_t) {
    return 0;
  }
  int &ret = dp[now_s][now_t];
  if (ret >= 0) {
    return ret;
  }
  if (s[now_s] > t[now_t]) {
    return ret = 1;
  }
  ret = f(now_s + 1, now_t);
  if (s[now_s] == t[now_t]) {
    ret |= f(now_s + 1, now_t + 1);
  }
  return ret;
}

int main() {
  int N, K;
  cin >> N >> K;
  --K;
  vector<string> answer(N);
  vector<pair<string, int>> data(N);
  for (int i = 0; i < N; ++i) {
    cin >> data[i].first;
    data[i].second = i;
  }
  sort(data.begin(), data.end());
  string current = "";
  for (int i = 0; i < K - 1; ++i) {
    current += 'A';
  }
  current += (char)('A' - 1);
  for (int i = 0; i < N; ++i) {
    t = current;
    s = data[i].first.substr(1, data[i].first.size() - 1);
    int L = 0;
    dp.clear();
    dp.resize(s.size(), vector<int>(t.size(), -1));
    bool done_larger = false;
    if (i > 0 && data[i].first[0] > data[i - 1].first[0]) {
      done_larger = true;
    }
    if (!done_larger) {
      if (f(0, 0) != 1) {
        cout << "NO" << endl;
        return 0;
      }
    }
    for (int j = 0; j < K; ++j) {
      int R = L;
      pair<char, int> optimal = make_pair('Z' + 1, 0);
      if (done_larger) {
        while (s.size() - R >= t.size() - j) {
          ++R;
        }
        for (int k = L; k < R; ++k) {
          optimal = min(optimal, make_pair(s[k], k));
        }
      } else {
        while (f(R, j) == 1) {
          ++R;
        }
        for (int k = L; k < R; ++k) {
          if (s[k] == t[j]) {
            if (f(k + 1, j + 1) == 1) {
              optimal = min(optimal, make_pair(s[k], k));
            }
          } else if (s[k] > t[j]) {
            if (s.size() - k >= t.size() - j) {
              optimal = min(optimal, make_pair(s[k], k));
            }
          }
        }
      }
      answer[data[i].second] += optimal.first;
      L = optimal.second + 1;
      done_larger |= (optimal.first > t[j]);
    }
    current = answer[data[i].second];
    answer[data[i].second] = data[i].first[0] + answer[data[i].second];
  }
  cout << "YES" << endl;
  for (int i = 0; i < N; ++i) {
    cout << answer[i] << endl;
  }
}
