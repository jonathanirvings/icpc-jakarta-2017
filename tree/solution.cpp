// Solution by Suhendry Effendy

/*
* O(N lg N + Q K^2)
*/
#include <bits/stdc++.h>
using namespace std;

#define REP(i,n)      for ( int i = 0, _n = (n); i < _n; i++ )
#define FOR(i,a,b)    for ( int i = (a), _n = (b); i <= _n; i++ )
#define FORD(i,a,b)   for ( int i = (a), _n = (b); i >= _n; i-- )
#define FORS(i,a,b,c) for ( int i = (a), _n = (b); i <= _n; i += c )
#define FOREACH(p,s)  for ( __typeof((s).begin()) p=(s).begin(); p!=(s).end(); p++)

const int maxn    = 100005;
const int logmaxn = 19;
const int maxk    = 105;
const int inf     = 0x7fffffff;

int N;
vector <int> con[maxn];
vector <int> chl[maxn];

void rootize(int curr, int parent) {
	FOREACH(p,con[curr]) if ( *p != parent ) {
		chl[curr].push_back(*p);
		rootize(*p,curr);
	}
}

struct tdata { int node, L; };
vector <tdata> arr;

int tour(int curr, int depth) {
	arr.push_back((tdata){curr,depth});
	if ( !chl[curr].empty() ) {
		FOREACH(p,chl[curr]) {
			tour(*p,depth+1);
			arr.push_back((tdata){curr,depth});
		}
	}
}

int pos[maxn];
int L[maxn];

int M[2*maxn][logmaxn];
int lg2[maxn*2];

void rmq_process() {
	REP(i,arr.size()) M[i][0] = i;
	for ( int j = 1; (1 << j) <= arr.size(); j++ ) {
		for ( int i = 0; i + (1 << j) - 1 < arr.size(); i++ ) {
			int a = i;
			int b = i + (1 << (j - 1));
			if ( arr[M[a][j-1]].L < arr[M[b][j-1]].L )
				M[i][j] = M[a][j-1];
			else
				M[i][j] = M[b][j-1];
		}
	}
}

int rmq_get(int a, int b) {
	if ( a > b ) swap(a,b);
	int k = lg2[b-a+1];
	if ( arr[M[a][k]].L < arr[M[b-(1<<k)+1][k]].L )
		return M[a][k];
	else
		return M[b-(1<<k)+1][k];
}

int dist(int u, int v) {
	if ( pos[u] > pos[v] ) swap(u,v);
	int idx = rmq_get(pos[u],pos[v]);
	return L[u] + L[v] - arr[idx].L * 2;
}

int flag[maxn] = {0};


int main(int argc, char *argv[]) {
	
	scanf( "%d", &N );
	REP(_,N-1) {
		int a, b;
		scanf( "%d %d", &a, &b );
		con[a].push_back(b);
		con[b].push_back(a);
	}

	rootize(1,1);
	tour(1,0);
	REP(i,arr.size()) pos[arr[i].node] = i;
	REP(i,arr.size()) L[arr[i].node]   = arr[i].L;
	
	rmq_process();

	int next = 1, k = -1;
	for ( int i = 1; i <= arr.size(); i++ ) {
		if ( i == next ) k++, next *= 2;
		lg2[i] = k;
	}


	FOR(i,1,N) flag[i] = -1;

	int Q;
	scanf( "%d", &Q );

	while ( Q-- ) {

		int K;
		int x[maxk];

		scanf( "%d", &K );
		REP(i,K) scanf( "%d", &x[i] );

		if ( K == 1 ) {
			puts( "0" );
			continue;
		}

		vector <int> cand;
		REP(i,K) REP(j,K) if ( i < j ) {
			int node = arr[rmq_get(pos[x[i]],pos[x[j]])].node;
			if ( flag[node] == Q ) continue;
			cand.push_back(node);
			flag[node] = Q;
		}

		int med_node = 0;
		int cost     = inf;

		FOREACH(p,cand) {
			int tcost = 0;
			REP(j,K) tcost += dist(x[j],*p);
			if ( tcost < cost ) cost = tcost, med_node = *p;
		}
		
		printf( "%d\n", cost );
	}

	return 0;
}
