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
	assert(1 <= N && N <= 40);
	assert(0 <= M && M <= 16);

	REP(i,3) {
		fgets(line, maxn, stdin);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 3);
		REP(j,v.size()) assert(0 <= v[j] && v[j] <= 1000);
		assert(v[i] == 0);
	}

	REP(_,M+1) {
		bool used[100] = {false};

		REP(i,3) {
			fgets(line, maxn, stdin);
			line[strlen(line)-1] = 0;
			v = splitInt(line);

			assert(v.size() > 0);
			
			int K = v[0];

			assert(v.size() == K + 1);

			FOR(j,1,v.size()-1)
				assert(1 <= v[j] && v[j] <= N);
			FOR(j,1,v.size()-2)
				assert(v[j] <= v[j+1]);

			FOR(j,1,v.size()-1) {
				assert(!used[v[j]]);
				used[v[j]] = true;
			}

		}

		FOR(i,1,N) assert(used[i]);
	}


	line[0] = 0;
	assert(fgets(line,maxn,stdin) == 0);
	assert(line[0] == 0);

	return 0;
}
