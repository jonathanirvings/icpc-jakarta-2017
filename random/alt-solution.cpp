// Second solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3000;

double dp_g[MAXN + 5][MAXN + 5];
double dp_f[MAXN + 5][MAXN + 5];

double g(int a, int b) {
	if (a + b == 0) {
		return 0;
	}
	double &ret = dp_g[a][b];
	if (ret == ret) return ret;
	ret = 1;
	if (a > 0) {
		ret += a * g(a - 1, b);
	}
	if (b > 0) {
		ret += b * g(a + 1, b - 1);
	}
	ret /= (a + b);
	return ret;
}

double f(int a, int b, int n) {
	if (a + b == 0) {
		return 0;
	}
	if (n == a + b) {
		double &ret = dp_f[a][b];
		if (ret == ret) return ret;
		ret = n;
		if (a > 0) {
			ret += a * f(a - 1, b, n);
		}
		if (b > 0) {
			ret += b * f(a + 1, b - 1, n);
		}
		ret /= (a + b);
		return ret;
	} else {
		return f(a, b, a + b) + g(a, b) * (n - (a + b));
	}
}

int main() {
	memset(dp_f, 0xff, sizeof(dp_f));
	memset(dp_g, 0xff, sizeof(dp_g));

	int T;
	scanf("%d", &T);
	while (T-- > 0) {
		int N, K;
		scanf("%d %d", &N, &K);
		int need_ones = 0;
		int need_twos = N;
		map<int, int> occurences;
		while (K-- > 0) {
			int A;
			scanf("%d", &A);
			if (occurences[A] == 0) {
				--need_twos;
				++need_ones;
			} else if (occurences[A] == 1) {
				--need_ones;
			}
			++occurences[A];
		}
		double answer = f(need_ones, need_twos, N);
		printf("%.7lf\n", answer);
	}
}

