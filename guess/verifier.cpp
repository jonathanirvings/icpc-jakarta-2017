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

vector<LL> splitLL( const string& s, const string& delim =" " ) {
    vector<string> tok = split( s, delim );
    vector<LL> res;
    for ( int i = 0 ; i != tok.size(); i++ )
        res.push_back( atoll( tok[i].c_str() ) );
    return res;
}

const int maxn = 1000001;


char line[maxn];
vector <LL> v;
vector <string> w;



int main()
{
	fgets(line, maxn, stdin);
	line[strlen(line)-1] = 0;
	v = splitLL(line);
	assert(v.size() == 2);

	LL N = v[0];
	LL K = v[1];
	assert(1 <= N && N <= 1000000000000000000LL);
	assert(1 <= K && K <= 50000);

	fgets(line, maxn, stdin);
	line[strlen(line)-1] = 0;
	w = split(line);
	assert(w.size() == 1);

	string s = w[0];

	REP(i,s.size()) assert(s[i] == '<' || s[i] == '>' || s[i] == '=');

	if ( s.back() == '=' ) {
		FOR(i,0,s.size()-2) assert(s[i] == '<' || s[i] == '>');
		assert(s.size() <= K);
	}
	if ( s.back() != '=' ) {
 		FOR(i,0,s.size()-2) assert(s[i] == '<' || s[i] == '>');
 		assert(s.size() == K);
	}


	line[0] = 0;
	assert(fgets(line,maxn,stdin) == 0);
	assert(line[0] == 0);

	return 0;
}
