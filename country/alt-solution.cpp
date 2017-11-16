// Second solution by Ashar Fuadi

#include <bits/stdc++.h>
using namespace std;

#define REP(i,n) for (int i = 0; i < n; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)

const int ALPH = 26, MAXN = 1005, MAXK = 205, MAXL = 200005;

int N, K;
pair<string, int> data[MAXN];
string ans[MAXN];

char buf[MAXK], buf2[MAXK];
int minR[ALPH][MAXL];

bool solve(int x) {
    const string& s = data[x].first;

    int n = s.size();
    REP(c, ALPH) {
        minR[c][n] = n;
        REPD(i, n) {
            if ('A'+c == s[i]) minR[c][i] = i;
            else minR[c][i] = minR[c][i+1];
        }
    }

    int fk = -1, fi = -1, fc = -1;

    if (n < K) return false;
    if (s[0] < buf[0]) return false;
    if (s[0] > buf[0]) {
        fk = 0, fi = 0, fc = s[0]-'A';
    } else {
        int i = 1;
        FOR(k, 1, K-1) {
            FOR(c, buf[k]-'A'+1, ALPH-1) {
                if (minR[c][i]+K-k-1 < n) {
                    fk = k, fi = minR[c][i], fc = c;
                    break;
                }
            }
            int c = buf[k]-'A';
            if (minR[c][i]+K-k-1 < n) {
                i = minR[c][i]+1;
            } else break;
        }
    }

    if (fk == -1) return false;

    REP(k, fk) buf2[k] = buf[k];
    buf2[fk] = 'A'+fc;

    int i = fi+1;
    FOR(k, fk+1, K-1) {
        REP(c, ALPH) {
            if (minR[c][i]+K-k-1 < n) {
                buf2[k] = 'A'+c;
                i = minR[c][i]+1;
                break;
            }
        }
    }

    ans[data[x].second] = string(buf2);
    REP(i, K) buf[i] = buf2[i];
    return true;
}

int main() {
    cin >> N >> K;
    REP(i, N) {
        string s;
        cin >> s;
        data[i] = make_pair(s, i);
    }

    sort(data, data+N);

    REP(k, K) buf[k] = 'A'-1;
    REP(i, N) {
        if (!solve(i)) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    REP(i, N) cout << ans[i] << endl;
}
