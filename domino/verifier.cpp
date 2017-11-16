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
	assert(1 <= N && N <= 100000);
	assert(1 <= M && M <= 100000);

	bool used[100005] = {false};

	REP(_,N) {
		fgets(line, maxn, stdin);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 3);

		int a = v[0];
		int b = v[1];
		int c = v[2];

		assert(1 <= a && a <= 2000000000);
		assert(1 <= b && b <= 2000000000);
		assert(1 <= c && c <= N);
		assert(!used[c]);
		used[c] = true;
	}


	line[0] = 0;
	assert(fgets(line,maxn,stdin) == 0);
	assert(line[0] == 0);

	return 0;
}
