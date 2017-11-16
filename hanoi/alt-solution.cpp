// Second solution by Ivan Adrian Koswara (converted from Python to C++ by Jonathan Irvin Gunawan)

//start of jonathanirvings' template v3.0.2 (BETA)

#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;
typedef pair<string,string> pss;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<pii> vii;
typedef vector<LL> vl;
typedef vector<vl> vvl;

double EPS = 1e-9;
int INF = 1000000005;
long long INFF = 1000000000000000005LL;
double PI = acos(-1);
int dirx[8] = {-1,0,0,1,-1,-1,1,1};
int diry[8] = {0,1,-1,0,-1,1,-1,1};

#ifdef TESTING
  #define DEBUG fprintf(stderr,"====TESTING====\n")
  #define VALUE(x) cerr << "The value of " << #x << " is " << x << endl
  #define debug(...) fprintf(stderr, __VA_ARGS__)
#else
  #define DEBUG 
  #define VALUE(x)
  #define debug(...)
#endif

#define FOR(a,b,c) for (int (a)=(b);(a)<(c);++(a))
#define FORN(a,b,c) for (int (a)=(b);(a)<=(c);++(a))
#define FORD(a,b,c) for (int (a)=(b);(a)>=(c);--(a))
#define FORSQ(a,b,c) for (int (a)=(b);(a)*(a)<=(c);++(a))
#define FORC(a,b,c) for (char (a)=(b);(a)<=(c);++(a))
#define REP(i,n) FOR(i,0,n)
#define REPN(i,n) FORN(i,1,n)
#define MAX(a,b) a = max(a,b)
#define MIN(a,b) a = min(a,b)
#define SQR(x) ((LL)(x) * (x))
#define RESET(a,b) memset(a,b,sizeof(a))
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define ALL(v) v.begin(),v.end()
#define ALLA(arr,sz) arr,arr+sz
#define SIZE(v) (int)v.size()
#define SORT(v) sort(ALL(v))
#define REVERSE(v) reverse(ALL(v))
#define SORTA(arr,sz) sort(ALLA(arr,sz))
#define REVERSEA(arr,sz) reverse(ALLA(arr,sz))
#define PERMUTE next_permutation
#define TC(t) while(t--)

inline string IntToString(LL a){
  char x[100];
  sprintf(x,"%lld",a); string s = x;
  return s;
}

inline LL StringToInt(string a){
  char x[100]; LL res;
  strcpy(x,a.c_str()); sscanf(x,"%lld",&res);
  return res;
}

inline string GetString(void){
  char x[1000005];
  scanf("%s",x); string s = x;
  return s;
}

inline string uppercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 'a' + 'A';
  return s;
}

inline string lowercase(string s){
  int n = SIZE(s); 
  REP(i,n) if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
  return s;
}

inline void OPEN (string s) {
  freopen ((s + ".in").c_str (), "r", stdin);
  freopen ((s + ".out").c_str (), "w", stdout);
}

//end of jonathanirvings' template v3.0.2 (BETA)

long long shortest(vvi start, vvi end, vvi cost)
{
  int N = SIZE(start[3]);
  long long dp[N+1][4][4];
  REP(K,N+1)
  {
    REP(S,4)
    {
      REP(E,4)
      {
        if (K == 0)
        {
          dp[K][S][E] = 0;
          continue;
        }
        int Si = S != 3 ? S : start[3][K-1];
        int Ei = E != 3 ? E : end[3][K-1];
        if (Si == Ei)
        {
          dp[K][S][E] = dp[K-1][S][E];
          continue;
        }
        int C = 3 - Si - Ei;
        dp[K][S][E] = min(dp[K-1][S][C] + cost[Si][Ei] + dp[K-1][C][E],
                          dp[K-1][S][Ei] + cost[Si][C] + dp[K-1][Ei][Si] + cost[C][Ei] + dp[K-1][Si][E]);
      }
    }
  }
  return dp[N][3][3];
}

vi baca(int K)
{
  vi ret(K);
  REP(i,K) scanf("%d",&ret[i]);
  return ret;
}

int main()
{
  int N,M; scanf("%d %d",&N,&M);
  vvi cost(3, vi(3));
  REP(i,3) REP(j,3) scanf("%d",&cost[i][j]);
  vector<vvi> konfig;
  REP(i,M+1)
  {
    int N1; scanf("%d",&N1); vi A = baca(N1);
    int N2; scanf("%d",&N2); vi B = baca(N2);
    int N3; scanf("%d",&N3); vi C = baca(N3);
    A.pb(-1);
    B.pb(-1);
    C.pb(-1);
    int pA = 0;
    int pB = 0;
    int pC = 0;
    vi posisi;
    REP(i,N)
    {
      if (A[pA] == i + 1)
      {
        posisi.pb(0);
        pA++;
      } else if (B[pB] == i + 1)
      {
        posisi.pb(1);
        pB++;
      } else if (C[pC] == i + 1)
      {
        posisi.pb(2);
        pC++;
      }
    }
    A.pop_back(); B.pop_back(); C.pop_back();
    konfig.pb({A, B, C, posisi});
  }
  vi urut;
  FOR(i,1,N+1) urut.pb(i);
  konfig.pb({urut, {}, {}, vi(N, 0)});
  konfig.pb({{}, urut, {}, vi(N, 1)});
  konfig.pb({{}, {}, urut, vi(N, 2)});

  long long shortest_cost[M+4][M+4];
  REP(i,M+4) REP(j,M+4) shortest_cost[i][j] = shortest(konfig[i],konfig[j],cost);

  vector<vector<LL>> prev_dp(M + 1, vector<LL>(1 << (M + 1)));
  FOR(i,1,M+1) prev_dp[i][1<<i] = shortest_cost[0][i];
  FOR(i,2,M+1)
  {
    vector<vector<LL>> dp(M + 1, vector<LL>(1 << (M + 1)));
    REP(combo,1<<(M+1)) if(__builtin_popcount(combo) == i && combo % 2 == 0)
    {
      FOR(curr,1,M+1) if(combo & (1 << curr))
      {
        int prev = combo ^ (1 << curr);
        dp[curr][combo] = LLONG_MAX;
        FOR(k,1,M+1) if(prev & (1 << k))
          MIN(dp[curr][combo], prev_dp[k][prev] + shortest_cost[k][curr]);
      }
    }
    prev_dp = dp;
  }
  if (M >= 1)
  {
    LL ans = LLONG_MAX;
    FOR(t,M+1,M+4) FOR(k,1,M+1) MIN(ans,prev_dp[k][(1<<(M+1))-2] + shortest_cost[k][t]);
    printf("%lld\n",ans);
  } else 
  {
    LL ans = LLONG_MAX;
    FOR(t,1,4) MIN(ans,shortest_cost[0][t]);
    printf("%lld\n",ans);
  }
  return 0;
}









