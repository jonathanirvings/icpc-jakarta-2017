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

long long N, K;
string S;
vector<long long> KEY_ANS, con;

int check(int id, long long left, long long right) {
	if (id == K) return ac();
	long long x = con[id];
	
	if (x < left || x > right) return wa();
	if (left == right) {
		if (S[id] == '=') return ac();
		return wa();
	}
	if (x - left >= right - x) {
		if (S[id] != '<') return wa();
		return check(id+1, left, x-1);
	} else {
		if (S[id] != '>') return wa();
		return check(id+1, x+1, right);
	}
}

int checks(istream& tc_in, istream& tc_out, istream& con_out) {
  tc_in >> N >> K;
  tc_in >> S;
  K = S.length();
  
  long long x;
    while (tc_out >> x) KEY_ANS.push_back(x);
  while (con_out >> x) con.push_back(x);
  
  if (KEY_ANS.size() != con.size()) return wa();
  if (KEY_ANS[0] == -1) {
    if (con[0] == -1) return ac();
    return wa();
  }
  
  return check(0, 1LL, N);
}

int main(int argc, char* argv[]) {
  ifstream tc_in(argv[1]);
  ifstream tc_out(argv[3]);

	return checks(tc_in, tc_out, cin);
}
