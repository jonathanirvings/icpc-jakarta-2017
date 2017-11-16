// Second solution by Jonathan Irvin Gunawan

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

// how to use : updates first, then initRMQ, then queries.
// 0-based
class RMQ
{
    vector<int> data;
    vector<vector<int> > rmq;
    vector<int> log2;
    int n;
    public:
    void reset(int n)
    {
        this->n = n;
        data.resize(n + 5);
        rmq.resize(n + 5);
        log2.resize(n + 5);
        int k = 0;
        for (int i = 1; i <= n; i = i * 2)
        {
            log2[i] = 1;
            ++k;
        }
        log2[1] = 0;
        REPN(i,n) rmq[i].resize(k + 2);
        FORN(i,1,n) log2[i] += log2[i-1];
    }
    void update(int a,int b)
    {
        ++a;
        data[a] = b;
    }
    void initRMQ(void)
    {
        REPN(i,n) rmq[i][0] = data[i];
        for (int j = 1; (1 << j) <= n; ++j)
        {
            REPN(i,n) 
            {
                rmq[i][j] = rmq[i][j-1];
                if (i + (1 << (j-1)) <= n)
                    MIN(rmq[i][j],rmq[i + (1 << (j-1))][j-1]);
            }
        }
    }
    int query(int a,int b)
    {
        ++a; ++b;
        int k = log2[b - a];
        return min(rmq[a][k],rmq[b - (1 << k) + 1][k]);
    }
};

class LCA {
public:
  int N, K;
  const vector<vector<int> > *adj;
  vector<int> height;
  vector<vector<int> > parent;
  vector<int> count;
  vector<int> waktu;
  vector<int> di_waktu;
  int counter;
  RMQ rmq;

  void init(int _N, vector<vector<int> > &_adj)
  {
    N = _N;
    K = 1;
    while ((1 << K) < N) ++K;
    height.resize(N);
    parent.resize(N);
    waktu.resize(N);
    di_waktu.resize(N);
    rmq.reset(N-1);
    REP(i,N) parent[i].resize(K);
    adj = &_adj;
    parent[0][0] = 0;
    height[0] = 0;
    counter = 0;
    dfs(0);
    fillParent();
    REP(i,N-1)
    {
      rmq.update(i,waktu[findLCAslow(di_waktu[i],di_waktu[i+1])]);
    }
    rmq.initRMQ();
  }

  int findLCAslow(int x,int y)
  {
    if (height[x] < height[y]) swap(x,y);
    FORD(i,K-1,0)
    {
      if (height[x] == height[y]) break;
      if (height[parent[x][i]] >= height[y]) x = parent[x][i];
    }
    if (x == y) return x;
    FORD(i,K-1,0)
    {
      if (parent[x][i] != parent[y][i])
      {
        x = parent[x][i];
        y = parent[y][i];
      }
    }
    return parent[x][0];
  }

  int findLCA(int x,int y)
  {
    if (x == y) return x;
    int a = waktu[x];
    int b = waktu[y];
    if (a > b) swap(a,b);
    return di_waktu[rmq.query(a,b-1)];
  }

  int dist(int x,int y)
  {
    int lca = findLCA(x,y);
    return height[x] + height[y] - 2 * height[lca];
  }

private:
  void dfs(int now)
  {
    di_waktu[counter] = now;
    waktu[now] = counter++;
    REP(i,SIZE((*adj)[now])) if((*adj)[now][i] != parent[now][0])
    {
      height[(*adj)[now][i]] = height[now] + 1;
      parent[(*adj)[now][i]][0] = now;
      dfs((*adj)[now][i]);
    }
  }

  void fillParent() 
  {
    FOR(i,1,K) REP(j,N)
    {
      parent[j][i] = parent[parent[j][i-1]][i-1];
    }
  }
};

int n,x,y,q,k;
vector<vector<int>> adj;
int input[105];
LCA lca;

int main()
{
  scanf("%d",&n);
  adj.resize(n);
  REP(i,n-1)
  {
    scanf("%d %d",&x,&y);
    --x; --y;
    adj[x].pb(y);
    adj[y].pb(x);
  }
  lca.init(n,adj);
  scanf("%d",&q);
  TC(q)
  {
    scanf("%d",&k);
    REP(i,k) 
    {
      scanf("%d",&input[i]);
      --input[i];
    }
    vector<int> candidates;
    REP(i,k) FOR(j,i+1,k) candidates.pb(lca.findLCA(input[i],input[j]));
    SORT(candidates);
    candidates.erase(unique(ALL(candidates)),candidates.end());
    int risan = INF;
    REP(i,SIZE(candidates)) 
    {
      int now = 0;
      REP(j,k) now += lca.dist(candidates[i],input[j]);
      MIN(risan,now);
    }
    if (k == 1) risan = 0;
    printf("%d\n",risan);
  }
  return 0;
}









