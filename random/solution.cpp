// Solution by Ammar Fathin Sabili

#include <bits/stdc++.h>
using namespace std;

int i,j,n,k,t,x;
int cum[3007];
double mem[3007][3007];

double DP(int x, int y) {
	if (x < 0 || y < 0) return 0.0;
	if (x == 0 && y == 0) return 0.0;
	if (mem[x][y] > -0.5) return mem[x][y];
	return mem[x][y] = 1.0/(x+y) + x*DP(x-1,y)/(x+y) + y*DP(x+1,y-1)/(x+y);
}

int main() {
	for (i=0 ; i<=3000 ; i++) {
		for (j=0 ; j<=3000 ; j++) {
			mem[i][j] = -1.00;
		}
	}

	scanf("%d",&t);
	while (t--) {
		scanf("%d%d",&n,&k);
		for (i=1 ; i<=n ; i++) cum[i] = 0;
		for (i=0 ; i<k ; i++) {
			scanf("%d",&x);
			cum[x]++;
		}
		
		int need1 = 0;
		int need2 = 0;
		for (i=1 ; i<=n ; i++) {
			if (cum[i] == 0) need2++;
			if (cum[i] == 1) need1++;
		}
		
		printf("%.9lf\n",DP(need1,need2)*n);
	}
}

