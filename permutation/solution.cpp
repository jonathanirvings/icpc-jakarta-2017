// Solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

const long long NO_CACHE = -1;

int N, Q;
int A[105];
int B[105];
int C[105];
int inverse_A[105];
vector<vector<int>> components;
int component_cycle_index[105];
int belongs_to[105];
int cycle_index[105][105];
long long K;
long long cached_number_of_solutions = NO_CACHE;

long long gcd(long long a, long long b) {
  return b == 0 ? a : gcd(b, a % b);
}

long long lcm(long long a, long long b) {
  return a / gcd(a, b) * b;
}

// returns a solution (x, y) where ax + by = gcd(a, b)
pair<long long, long long> extended_euclid(long long a, long long b) {
  if (b == 0) {
    return make_pair(1, 0);
  }
  pair<long long, long long> temp = extended_euclid(b, a % b);
  return make_pair(temp.second, temp.first - (a / b) * temp.second);
}

// finds a smallest non-negative integer x such that
// x % a1 = b1, x % a2 = b2
long long CRT(long long a1, long long b1, long long a2, long long b2) {
  pair<long long, long long> solution = extended_euclid(a1, a2);
  long long x = (b1 * solution.second * a2 + b2 * solution.first * a1) % lcm(a1, a2);
  return x < 0 ? x + lcm(a1, a2) : x;
}

void print_vector(vector<int> v) {
  return;
  printf("{");
  for (int i : v) {
    printf("%d ", i);
  }
  puts("}");
}

long long count_number_of_solutions() {
  if (cached_number_of_solutions != NO_CACHE) {
    return cached_number_of_solutions;
  }
  long long result = 1;
  long long now = 1;
  for (int i = 0; i < components.size(); ++i) {
    if (component_cycle_index[i] == -1) {
      long long divisor = gcd(now, components[i].size());
      result *= components[i].size() / divisor;
    } else {
    }
    now = lcm(now, components[i].size());
  }
  return cached_number_of_solutions = result;
}

int main() {
  scanf("%d %d", &N, &Q);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
    --A[i];
    B[i] = A[i];
    inverse_A[A[i]] = i;
  }
  memset(cycle_index, -1, sizeof(cycle_index));
  memset(belongs_to, -1, sizeof(belongs_to));
  for (int i = 0; i < N; ++i) {
    if (belongs_to[i] != -1) {
      continue;
    }
    int now = i;
    vector<int> component;
    do {
      belongs_to[now] = components.size();
      component.push_back(now);
      now = inverse_A[now];
    } while (now != i);
    components.push_back(component);
  }
  for (int loop = 0; loop < N; ++loop) {
    for (int i = 0; i < N; ++i) {
      cycle_index[i][B[i]] = loop % components[belongs_to[i]].size();
    }
    for (int i = 0; i < N; ++i) {
      C[i] = B[A[i]];
    }
    for (int i = 0; i < N; ++i) {
      B[i] = C[i];
    }
  }
  while (Q--) {
    scanf("%lld", &K);
    memset(component_cycle_index, -1, sizeof(component_cycle_index));
    // current solution : x % now.first = now.second
    pair<long long, long long> now = make_pair(1, 0);
    for (int i = 0; i < N; ++i) {
      cached_number_of_solutions = NO_CACHE;
      // printf("%lld %lld\n", now.first, now.second);
      if (component_cycle_index[belongs_to[i]] != -1) {
        continue;
      }
      vector<int> component = components[belongs_to[i]];
      sort(component.begin(), component.end());
      print_vector(component);
      for (int j = 0; j < component.size(); ++j) {
        long long divisor = gcd(now.first, component.size());
        long long mod_divisor = now.second % divisor;
        // printf("%d %d %d %d\n", i, component[j], cycle_index[i][component[j]], divisor);
        if (cycle_index[i][component[j]] % divisor != mod_divisor) {
          continue;
        }
        component_cycle_index[belongs_to[i]] = cycle_index[i][component[j]];
        long long number_of_solutions = count_number_of_solutions();
        // printf(">>>%lld %lld\n", number_of_solutions, K);
        if (K > number_of_solutions) {
          K -= number_of_solutions;
        } else {
          long long temporary = CRT(now.first / divisor,
                                    now.second / divisor,
                                    component.size() / divisor,
                                    cycle_index[i][component[j]] / divisor);
          now = make_pair(lcm(now.first, component.size()),
                          temporary * divisor + (now.second % divisor));
          break;
        }
      }
    }
    printf("%lld\n", now.second + 1);
  }
}