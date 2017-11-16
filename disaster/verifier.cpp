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

long long distance(int x, int y, int fx, int fy)
{
	return (long long)(fx - x) * (fx - x)
	     + (long long)(fy - y) * (fy - y);
}

int main()
{
	fgets(line, maxn, stdin);
	line[strlen(line)-1] = 0;
	v = splitInt(line);
	assert(v.size() == 5);

	int x1 = v[0];
	int y1 = v[1];
	int x2 = v[2];
	int y2 = v[3];
	int N  = v[4];
	assert(-1000000 <= x1 && x1 < x2 && x2 <= 1000000);
	assert(-1000000 <= y1 && y1 < y2 && y2 <= 1000000);
	assert(0 <= N && N <= 1000);

	set <pair<int,int> > s;

	REP(_,N) {
		fgets(line, maxn, stdin);
		line[strlen(line)-1] = 0;
		v = splitInt(line);
		assert(v.size() == 3);

		int fx = v[0];
		int fy = v[1];
		int r  = v[2];
		assert(-1000000 <= fx && fx <= 1000000);
		assert(-1000000 <= fy && fy <= 1000000);
		assert(1 <= r && r <= 2000000);
		assert(s.find(make_pair(fx,fy)) == s.end());
		s.insert(make_pair(fx,fy));

		assert(distance(x1, y1, fx, fy) >= (long long)r * r);
		assert(distance(x2, y2, fx, fy) >= (long long)r * r);
	}



	line[0] = 0;
	assert(fgets(line,maxn,stdin) == 0);
	assert(line[0] == 0);

	return 0;
}
