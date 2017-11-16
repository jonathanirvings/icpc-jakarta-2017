// Input verifier by Suhendry Effendy

#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0,_n=(n);i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FOREACH(it,arr) for (__typeof((arr).begin()) it=(arr).begin(); it!=(arr).end(); it++)

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
	assert(v.size() == 2);

	int N = v[0];
	int M = v[1];
	assert(1 <= N && N <= 100);
	assert(1 <= M && M <= 100);

	fgets(line, maxn, stdin);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == M);

	vector <int> T = v;
	REP(i,M) assert(0 <= T[i] && T[i] <= 100);

	REP(_,N) {
		fgets(line, maxn, stdin);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == M);
	
		REP(j,M) assert(0 <= v[j] && v[j] <= T[j]);		
	}

	line[0] = 0;
	assert(fgets(line,maxn,stdin) == 0);
	assert(line[0] == 0);

	return 0;
}
