#include <bits/stdc++.h>
using namespace std;

int wa() {
  cout << "WA" << endl;
  return 0;
}

int ac() {
  // cout << "AC" << endl;
  return 0;
}

int N, K;

// checks whether t is a subsequence of s
bool is_subsequence(string s, string t)
{
  int L = 0;
  for (int i = 0; i < t.size(); ++i) {
    while (L < s.size() && s[L] != t[i]) {
      ++L;
    }
    if (L == s.size()) return false;
    ++L;
  }
  return true;
}

int checks(istream& tc_in, istream& tc_out, istream& con_out) {
  tc_in >> N >> K;
  
  string s_tc, s_con;
  getline(tc_out, s_tc);
  getline(con_out, s_con);

  if (s_tc != s_con) return wa();
  if (s_tc == "NO") 
  {
    if (getline(con_out, s_con)) {
      return wa();
    }
    return ac();
  }

  vector<string> input(N);
  vector<string> output(N);
  vector<int> order(N);

  getline(tc_in, input[0]);
  for (int i = 0; i < N; ++i) {
    order[i] = i;
    getline(tc_in, input[i]);
    getline(con_out, output[i]);

    if (output[i].size() != K) return wa();
    if (output[i][0] != input[i][0]) return wa();
    if (!is_subsequence(input[i], output[i])) return wa();
  }

  if (getline(con_out, s_con)) {
    return wa();
  }

  auto f = [&](const int &a, const int &b) -> bool
  {
    return input[a] < input[b];
  };

  sort(order.begin(), order.end(), f);
  for (int i = 1; i < N; ++i) {
    if (output[order[i]] <= output[order[i - 1]]) return wa();
  }
  return ac();
}

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[3]);

  return checks(tc_in, tc_out, cin);
}
