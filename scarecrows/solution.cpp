// Solution by Ashar Fuadi

/*
 * Sacred Scarecrows, INC/ICPC Jakarta 2017
 * Ashar Fuadi
 * Time complexity: O(2^R . C)
*/

#include <bits/stdc++.h>

#define REP(i,n) for (int i = 0, _n = n; i < _n; i++)
#define RESET(c,v) memset(c, v, sizeof c)

using namespace std;

/***********************************************************/

const int MAXR = 17, MAXC = 1005, MOD = 1000000007;
using ll = long long;

int R, C;
char G[MAXR][MAXC];

int emptySquares[MAXC];
int ans;

ll dp[MAXC][2];

void solve(int cnt) {
    dp[C][0] = dp[C][1] = 1;
    for (int j = C-1; j >= 0; j--) {
        int ways = (1 << emptySquares[j]) - 1;
        dp[j][0] = ways * dp[j+1][1] % MOD;
        dp[j][1] = ways * dp[j+1][1] % MOD;
        dp[j][1] = (dp[j][1] + dp[j+1][0]) % MOD;
    }
    if (cnt % 2) ans = (ans - dp[0][1] + MOD) % MOD;
    else ans = (ans + dp[0][1]) % MOD;
}

void dfs(int i, int cnt) {
    if (i == R) {
        solve(cnt);
        return;
    }

    dfs(i+1, cnt);

    REP(j, C) emptySquares[j] -= (G[i][j] == '.');
    dfs(i+1, cnt+1);
    REP(j, C) emptySquares[j] += (G[i][j] == '.');
}

int main() {
    scanf("%d %d", &R, &C);
    REP(i, R) {
        scanf("%s", G[i]);
        REP(j, C) emptySquares[j] += (G[i][j] == '.');
    }
    dfs(0, 0);
    printf("%d\n", ans);
}
