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


int main()
{
	fgets(line, maxn, stdin);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 1);

	int T = v[0];
	assert(1 <= T && T <= 100000);

	LL total = 0;

	REP(_,T) {
		fgets(line, maxn, stdin);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 2);

		int N = v[0];
		int K = v[1];
		assert(1 <= N && N <= 3000);
		assert(0 <= K && K <= 100000);

		fgets(line, maxn, stdin);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == K);

		REP(i,K) assert(1 <= v[i] && v[i] <= N);

		bool okay = false;
		int cnt[5000] = {0};
		REP(i,K) cnt[v[i]]++;
		FOR(i,1,N) if ( cnt[i] < 2 ) okay = true;
		assert(okay);

		total += K;
	}

	assert(0 <= total && total <= 100000);

	line[0] = 0;
	assert(fgets(line,maxn,stdin) == 0);
	assert(line[0] == 0);

	return 0;
}
