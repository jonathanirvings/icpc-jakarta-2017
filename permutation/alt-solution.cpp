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

LL mod(LL a, LL b) {
  LL res = a % b;
  if (res < 0) {
    res += b;
  }
  return res;
}

vl extended_euclid(LL A, LL B)
{
  if (A < B)
  {
    vl res = extended_euclid(B, A);
    return {res[1], res[0], res[2]};
  }
  vl P = {1, 0};
  vl Q = {0, 1};
  vl R = {A, B};
  while (R[SIZE(R) - 1] != 0)
  {
    LL quot = R[SIZE(R)-2] / R[SIZE(R)-1];
    P.pb(P[SIZE(P)-2] - quot * P[SIZE(P)-1]);
    Q.pb(Q[SIZE(Q)-2] - quot * Q[SIZE(Q)-1]);
    R.pb(R[SIZE(R)-2] - quot * R[SIZE(R)-1]);
  }
  return {P[SIZE(P)-2],Q[SIZE(Q)-2],R[SIZE(R)-2]};
}

vl crt(LL A1, LL M1, LL A2, LL M2)
{
  vl temp = extended_euclid(M1, M2); LL N1 = temp[0]; LL N2 = temp[1]; LL G = temp[2];
  if (G != 1)
  {
    if (mod(A1, G) != mod(A2, G)) return {-1};
    vl temp = crt(A1 / G, M1 / G, A2 / G, M2 / G); LL A = temp[0]; LL M = temp[1];
    return {A * G + mod(A1, G), M * G};
  }
  LL M = M1 * M2;
  LL A = A1 * M2 * N2 + A2 * M1 * N1;
  A = mod(A, M);
  return {A, M};
}

int main()
{
  LL N, Q; scanf("%lld %lld", &N, &Q);
  vl A(N); for (LL i = 0; i < N; ++i) {scanf("%lld", &A[i]); --A[i];}

  vl cycle_length(N, 0);
  LL ptr = 0;
  while (true)
  {
    while (ptr < N && cycle_length[ptr] != 0) ++ptr;
    if (ptr == N) break;
    vl vlsited = {ptr};
    while (A[vlsited[SIZE(vlsited)-1]] != vlsited[0])
    {
      vlsited.pb(A[vlsited[SIZE(vlsited)-1]]);
    }
    cycle_length[vlsited[0]] = SIZE(vlsited);
    FOR(i,1,SIZE(vlsited))
    {
      cycle_length[vlsited[i]] = 1;
    }
  }

  vl L(N + 1, 1);
  vector<vvl> kemungkinan;
  REP(i,N)
  {
    LL g = __gcd(L[i], cycle_length[i]);
    L[i + 1] = (L[i] * cycle_length[i]) / g;
    if (cycle_length[i] == 1)
    {
      kemungkinan.pb({{-1}});
    } else 
    {
      kemungkinan.pb(vector<vl>(g, vector<LL>{}));
      ptr = i;
      REP(j,cycle_length[i])
      {
        kemungkinan[SIZE(kemungkinan)-1][mod(j, g)].pb(ptr);
        ptr = A[ptr];
      }
    }
  }
  vl M(N + 1); REP(i,N+1) M[i] = L[SIZE(L)-1] / L[i];

  REP(query,Q)
  {
    LL K; scanf("%lld",&K); --K;

    vl B(N, 0);
    REP(i,N)
    {
      B[i] = K / M[i + 1];
      K = mod(K, M[i + 1]);
    }
    LL T = 0;
    REP(i,N)
    {
      if (cycle_length[i] == 1) continue;
      LL Tmod = mod(T, SIZE(kemungkinan[i]));
      vl v = kemungkinan[i][Tmod]; sort(v.begin(), v.end()); LL elemen = v[B[i]];
      LL posisi = find(kemungkinan[i][Tmod].begin(), kemungkinan[i][Tmod].end(), elemen) - kemungkinan[i][Tmod].begin();
      T = crt(T, L[i], posisi * SIZE(kemungkinan[i]) + Tmod, cycle_length[i])[0];
    }
    if (T == 0) T = L[SIZE(L) - 1];
    printf("%d\n", T);
  }
  return 0;
}



















