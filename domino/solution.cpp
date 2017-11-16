// Solution by Suhendry Effendy

#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for(int i=0,_n=(n);i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FOREACH(it,arr) for (__typeof((arr).begin()) it=(arr).begin(); it!=(arr).end(); it++)

const int maxn = 1000005;

int N, M;

struct triple { int u, v, w; };
bool operator < (const triple x, const triple y) { return x.w < y.w; };

triple arr[maxn];

map <int,int> cap;

int main(int argc, char *argv[]) {
	
	scanf( "%d %d", &N, &M );
	REP(i,N) scanf( "%d %d %d", &arr[i].u, &arr[i].v, &arr[i].w );
	
	sort(arr,arr+N);

	int ans = 0;
	REP(i,N) {
		if ( cap[arr[i].u] == 0 ) {
			cap[arr[i].u] += M - 1;
			cap[arr[i].v] += M;
			ans++;
		}
		else {
			cap[arr[i].u]--;
			cap[arr[i].v] += M;
		}
	}

	printf( "%d\n", ans );
	
	return 0;
}
