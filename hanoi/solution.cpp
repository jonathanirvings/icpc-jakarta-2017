// Solution by Jonathan Irvin Gunawan

#include <bits/stdc++.h>
using namespace std;

const long long NOT_COMPUTED = -1;

map<vector<int>, long long> ddp[3][2];

long long move(int number_of_disks,
               int largest_disk_destination,
               bool to_same,
               vector<int> &position,
               const vector<int> &destination,
               const vector<vector<int>> &cost) {
  if (number_of_disks == 0) {
    return 0;
  }
  if (position[number_of_disks - 1] == largest_disk_destination) {
    return move(number_of_disks - 1,
                to_same ? largest_disk_destination
                        : destination[number_of_disks - 2],
                to_same,
                position,
                destination,
                cost);
  }
  int source = position[number_of_disks - 1];
  vector<int> important_position(number_of_disks);
  for (int i = 0; i < number_of_disks; ++i) {
    important_position[i] = position[i];
  }
  if (ddp[largest_disk_destination][to_same].count(important_position)) {
    for (int i = 0; i < number_of_disks; ++i) {
      position[i] = to_same ? largest_disk_destination : destination[i];
    }
    return ddp[largest_disk_destination][to_same][important_position];
  }
  long long total_cost = 0;
  int transit_position = 0 ^ 1 ^ 2 ^ source ^ largest_disk_destination;
  vector<int> position_one = position;
  long long cost_one = LLONG_MAX;
  vector<int> position_two = position;
  long long cost_two = LLONG_MAX;
  {
    cost_one = 0;
    cost_one += move(number_of_disks - 1,
                     transit_position,
                     true,
                     position_one,
                     destination,
                     cost);
    cost_one += cost[source][largest_disk_destination];
    position_one[number_of_disks - 1] = largest_disk_destination;
    cost_one += move(number_of_disks - 1,
                     to_same ? largest_disk_destination
                             : destination[number_of_disks - 2],
                     to_same,
                     position_one,
                     destination,
                     cost);
  }
  if (true) {
    cost_two = 0;
    cost_two += move(number_of_disks - 1,
                     largest_disk_destination,
                     true,
                     position_two,
                     destination,
                     cost);
    cost_two += cost[source][transit_position];
    position_two[number_of_disks - 1] = transit_position;
    cost_two += move(number_of_disks - 1,
                     source,
                     true,
                     position_two,
                     destination,
                     cost);
    cost_two += cost[transit_position][largest_disk_destination];
    position_two[number_of_disks - 1] = largest_disk_destination;
    cost_two += move(number_of_disks - 1,
                     to_same ? largest_disk_destination
                             : destination[number_of_disks - 2],
                     to_same,
                     position_two,
                     destination,
                     cost);
  }
  if (cost_one < cost_two) {
    total_cost = cost_one;
    position = position_one;
  } else {
    total_cost = cost_two;
    position = position_two;
  }
  return ddp[largest_disk_destination][to_same][important_position]
         = total_cost;
}

long long calculate_distance(const vector<int> &from_position,
                             const vector<int> &to_position,
                             const vector<vector<int>> &cost) {
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 2; ++j) {
      ddp[i][j].clear();
    }
  }
  int N = from_position.size();
  vector<int> position(from_position);
  return move(N,
              to_position[N - 1],
              false,
              position,
              to_position,
              cost);
}

long long tsp(int current_node,
              int visited_nodes,
              vector<vector<long long>> &dp,            
              const vector<vector<long long>> &distance,
              const vector<vector<int>> &positions,
              const vector<vector<int>> &cost) {
  int K = distance.size();
  if (dp[current_node][visited_nodes] != NOT_COMPUTED) {
    return dp[current_node][visited_nodes];
  }
  if (visited_nodes == (1 << K) - 1) {
    int N = positions[current_node].size();
    vector<int> zeros(N, 0);
    vector<int> ones(N, 1);
    vector<int> twos(N, 2);
    long long res = LLONG_MAX;
    for (const vector<int> &to_position : {zeros, ones, twos}) {
      res = min(res, calculate_distance(positions[current_node],
                                        to_position, cost));
    }
    return dp[current_node][visited_nodes] = res;
  }
  long long res = LLONG_MAX;
  for (int i = 0; i < K; ++i) {
    if (visited_nodes & (1 << i)) {
    } else {
      res = min(res, distance[current_node][i] + tsp(i,
                                                     visited_nodes | (1 << i),
                                                     dp,
                                                     distance,
                                                     positions,
                                                     cost));
    }
  }
  return dp[current_node][visited_nodes] = res;
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  vector<vector<int>> cost(3);
  for (int i = 0; i < 3; ++i) {
    cost[i].resize(3);
    for (int j = 0; j < 3; ++j) {
      scanf("%d", &cost[i][j]);
    }
  }
  vector<vector<int>> positions(M + 1, vector<int>(N));
  for (int i = 0; i < M + 1; ++i) {
    for (int j = 0; j < 3; ++j) {
      int number_of_disks;
      scanf("%d", &number_of_disks);
      while (number_of_disks--) {
        int disk_index;
        scanf("%d", &disk_index);
        positions[i][disk_index - 1] = j;
      }
    }
  }
  vector<vector<long long>> distance(M + 1, vector<long long>(M + 1));
  for (int i = 0; i < M + 1; ++i) {
    for (int j = 0; j < M + 1; ++j) {
      distance[i][j] = calculate_distance(positions[i], positions[j], cost);
    }
  }
  vector<vector<long long>> dp(M + 1,
                               vector<long long>(1 << (M + 1), NOT_COMPUTED));
  long long answer = tsp(0, (1 << 0), dp, distance, positions, cost);
  printf("%lld\n", answer);
}
