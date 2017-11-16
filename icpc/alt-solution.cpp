// Second solution by Suhendry Effendy

#include <cstdio>
using namespace std;

#define REP(i,n) for(int i=0,_n=(n);i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)

const int maxn = 105;
const int maxm = 105;

int N, M;
int T[maxm], S[maxm];
int solve[maxn] = {0}, hi = -1, ans = 0;

int main() {
	
	scanf( "%d %d", &N, &M );
	REP(j,M) scanf( "%d", &T[j] );
	FOR(i,1,N) {
		REP(j,M) scanf( "%d", &S[j] );
		REP(j,M) if ( S[j] == T[j] ) solve[i]++;
		if ( solve[i] > hi ) hi = solve[i], ans = i;
	}

	printf( "%d\n", ans );

	return 0;
}
