// Solution by Ammar Fathin Sabili

#include <bits/stdc++.h>
using namespace std;

long long n,k,i;
char s[200007];

bool can(long long sta, long long fin, int pos) {
	if (sta == fin) return true;
	if (s[pos] == '=') return false;
	
	if (s[pos] == '<') {
		long long mid = (sta+fin+1)/2;
		return can(sta,mid-1,pos+1);
	}
	if (s[pos] == '>') {
		long long mid = (sta+fin-1)/2;
		return can(mid+1,fin,pos+1);
	}
}

void solve(long long sta, long long fin, int pos) {
	if (s[pos] == '=') {
		assert(sta == fin);
		printf("%lld\n",sta);
		return;
	}
	
	if (s[pos] == '<' && can(sta,fin-1,pos+1)) {
		printf("%lld ",fin);
		solve(sta,fin-1,pos+1);
		return;
	}
	if (s[pos] == '>' && can(sta+1,fin,pos+1)) {
		printf("%lld ",sta);
		solve(sta+1,fin,pos+1);
		return;
	}
	
	if (s[pos] == '<') {
		long long mid = (sta+fin+1)/2;
		printf("%lld ",mid);
		solve(sta,mid-1,pos+1);
		return;
	}
	if (s[pos] == '>') {
		long long mid = (sta+fin-1)/2;
		printf("%lld ",mid);
		solve(mid+1,fin,pos+1);
		return;
	}
}

int main() {
	scanf("%lld%lld",&n,&k);
	scanf("%s",s);
	k = strlen(s);
	
	if (s[k-1] == '=' && k > n) {
		printf("-1\n");
		return 0;
	}
	if (s[k-1] != '=' && k >= n) {
		printf("-1\n");
		return 0;
	}
	
	if (s[k-1] != '=') {
		long long sta = 1;
		long long fin = n;
		for (i=0 ; i<k ; i++) {
			if (s[i] == '<') printf("%lld",fin--);
			if (s[i] == '>') printf("%lld",sta++);
			if (i == k-1) printf("\n"); else printf(" ");
		}
		return 0;
	}
	
	if (!can(1,n,0)) {
		printf("-1\n");
		return 0;
	}
	solve(1,n,0);
}
