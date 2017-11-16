// Second solution by Alham Fikri Aji

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <stack>
#include <string>
#include <map>
#define ll long long
#define read(x) scanf("%d",&x);
#define readll(x) cin>>x;
#define FOR(x,a,b) for(int x=a;x<b;x++)
#define MP make_pair
#define PB push_back
#define pii pair<int,int>
#define readN(N,X) for(int i=0;i<N;i++) cin>>X[i];
#define pff pair<double,double>
using namespace std;

long long fastpow(int a, int b, int MOD)
{
    long long x=1,y=a; 
    while(b > 0)
    {
        if(b%2 == 1)
        {
            x=(x*y) % MOD;
        }
        y = (y*y) % MOD;
        b /= 2;
    }
    return x;
}

long long InverseEuler(int n, int MOD)
{
    return fastpow(n,MOD-2,MOD);
}
 
long long f[300000];
bool init;
long long C(int n, int r, int MOD)
{
    if (!init){
        init=1;
        f[0]=1;
        for (int i=1; i<300000;i++)
            f[i]= (f[i-1]*i) % MOD;
        
    }
    return (f[n]*((InverseEuler(f[r], MOD) * InverseEuler(f[n-r], MOD)) % MOD)) % MOD;
}

multiset<pair<int,int>> lho;
multiset<int> ans;

void del(int v, int t){
    if (lho.count({v,t}) == 1){
        set<pair<int,int>>::iterator it = lho.lower_bound({v,t});
        //cout<<(*it).first<<endl;
        vector<pair<int,int>> all;
        if (it != lho.begin()){
            it--;
            auto now = (*it); all.push_back(now);
            if (now.second != t) ans.erase(ans.find(abs(v - now.first)));
            it++;
        }
        it++;
        if (it != lho.end()){
            auto now = (*it); all.push_back(now);
            if (now.second != t) ans.erase(ans.find(abs(v - now.first)));
        }
        if (all.size() == 2) {
            if (all[0].second != all[1].second) ans.insert(abs(all[1].first - all[0].first));
        }
    }
    lho.erase(lho.find({v,t}));
}

void add(int v, int t){
    if (lho.count({v,t}) == 0){
        set<pair<int,int>>::iterator it = lho.lower_bound({v,t});
        //cout<<(*it).first<<endl;
        vector<pair<int,int>> all;
        if (it != lho.begin()){
            it--;
            auto now = (*it); all.push_back(now);
            if (now.second != t) ans.insert(abs(v - now.first));

            it++;
        }
        if (it != lho.end()){
            auto now = (*it); all.push_back(now);
            if (now.second != t) ans.insert(abs(v - now.first));
        }
        if (all.size() == 2) {
            if (all[0].second != all[1].second) ans.erase(ans.find(abs(all[1].first - all[0].first)));
        }
    }
    lho.insert({v,t});
}


int Q;
int N;
int M;
vector<int> path[100005];
int S[100005];
int flag[100005];
bool bubar;
void dfs(int pos, int flip){
    if (flag[pos] == flip) return;
    if (flag[pos] == -1) flag[pos] = flip;
    if (flag[pos] != flip) {
        bubar = 1;
        return;
    }
    for (auto a:path[pos]) dfs(a, flip ^ 1);
}

int main(){
   std::ios::sync_with_stdio(false); 
   cin>>N>>M;
   memset(flag, -1, sizeof(flag));
   for (int i=0;i<N;i++) cin>>S[i];
   for (int i=0;i<M;i++){
    int a,b;
    cin>>a>>b;
    a--;b--;
    path[a].push_back(b);
    path[b].push_back(a);
   }
   dfs(0,0);
   cin>>Q;
   if (!bubar) for (int i=0;i<N;i++) add(S[i], flag[i]);
   for (int i=0;i<Q;i++){
        int wo,a,b;
        cin>>wo>>a>>b;
        a--;b--;
        if (wo == 0){
            b++;
            if (bubar) continue;
            del(S[a], flag[a]);
            add(b, flag[a]);
            S[a] = b;
        }
        else {
            if (bubar || flag[a] == flag[b]) cout<<0<<endl;
            else cout<<*ans.begin()<<endl;
        }
   }
}
