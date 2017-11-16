// Second solution by Suhendry Effendy

#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )
#define FORD(i,a,b)   for ( int i = (a), _n = (b); i >= _n; i-- )
#define FORS(i,a,b,c) for ( int i = (a), _n = (b); i <= _n; i += c )
#define FOREACH(p,s)  for ( __typeof((s).begin()) p=(s).begin(); p!=(s).end(); p++)

const int maxn = 100005;

int N, K, T;
int A[maxn];
int L = 0, R = 0;

int main(int argc, char *argv[]) {
	
	scanf( "%d %d %d", &N, &K, &T );
	REP(i,N) scanf( "%d", &A[i] );

	sort(A,A+N);

	if ( K == N )         { printf( "0\n" );  return 0; }
	if ( A[K-1] != A[K] ) { printf( "0\n" );  return 0; }
	if ( T == 0 )         { printf( "-1\n" ); return 0; }

	int i;
	for ( i = K - 1; i >= 0 && A[i] == A[K-1]; i-- ) L++;
	for ( i = K;     i  < N && A[i] == A[K]  ; i++ ) R++;
	
	int ans = min(L,R);
	if ( A[K] == 0 ) ans = R;
	if ( A[K] == T ) ans = L;

	printf( "%d\n", ans );

	return 0;
}
