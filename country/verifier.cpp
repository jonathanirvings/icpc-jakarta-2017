// Input verifier by Suhendry Effendy

#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0,_n=(n);i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FOREACH(it,arr) for (__typeof((arr).begin()) it=(arr).begin(); it!=(arr).end(); it++)

typedef long long LL;

vector<string> split( const string& s, const string& delim =" " ) {
	vector<string> res;
	string t;
	REP(i,s.size()) {
		if ( delim.find(s[i]) == string::npos ) t += s[i];
		else if ( !t.empty() ) { res.push_back(t); t = ""; }
	}
	if ( !t.empty() ) res.push_back(t);
	return res;
}

vector<int> splitInt( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<int> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoi( tok[i].c_str() ) );
    return res;
}

const int maxn = 1000001;


char line[maxn];
vector <int> v;
vector <string> w;


int p[100005], r[100005];
int link(int x, int y) {
	if ( r[x] == r[y] ) r[x]++;
	if ( r[x]  < r[y] ) p[x] = y; else p[y] = x;
}
int find(int x) {
	if ( p[x] != x ) p[x] = find(p[x]);
	return p[x];
}


int main()
{
	fgets(line, maxn, stdin);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 2);

	int N = v[0];
	int K = v[1];
	assert(1 <= N && N <= 1000);
	assert(1 <= K && K <= 200);

	set <string> s;
	LL total = 0;

	REP(_,N) {
		fgets(line, maxn, stdin);
		line[strlen(line)-1] = 0;
		w = split(line);
		assert(w.size() == 1);

		string str = w[0];
		assert(1 <= str.size() && str.size() <= 200000);
		REP(i,str.size()) assert('A' <= str[i] && str[i] <= 'Z');

		assert(s.find(str) == s.end());

		s.insert(str);
		total += str.size();
	}

	assert(total <= 200000);
	

	line[0] = 0;
	assert(fgets(line,maxn,stdin) == 0);
	assert(line[0] == 0);

	return 0;
}
