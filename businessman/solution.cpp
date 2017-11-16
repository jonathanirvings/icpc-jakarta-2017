// Solution by Jonathan Irvin Gunawan

/**
 * "Business" solution
 * Jonathan Irvin Gunawan
**/

//start of jonathanirvings' template v2.0.0 (BETA)

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <deque>
#include <string>
#include <string.h>
#include <vector>
#include <stack>
#include <queue>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <set>
#include <time.h>
#include <bitset>
#include <list>
using namespace std;

struct costs_elem {
	int cost, color, index;
	bool operator<(const costs_elem& rhs) const
    {
    	return make_pair(cost,make_pair(color,index)) < make_pair(rhs.cost,make_pair(rhs.color,rhs.index));
    }
};

int n,m,a,b,q;
int color[100005];
vector<int> adj[100005];
vector<int> nodes[2];
bool bipartite;
int queryType;
multiset<costs_elem> costs;
multiset<int> answers;
int cost[100005];
int initCost[100005];

void dfs(int now) {
	nodes[color[now]].push_back(now);
	for (int i = 0; i < (int)adj[now].size(); ++i) {
		if (color[adj[now][i]] == -1) {
			color[adj[now][i]] = 1 - color[now];
			dfs(adj[now][i]);
		} else if (color[adj[now][i]] == color[now]) {
			bipartite = false;
		}
	}
}

void init() {
	if (!bipartite) {
		return;
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < (int)nodes[i].size(); ++j) {
			costs.insert((costs_elem){cost[nodes[i][j]],i,nodes[i][j]});
		}
	}
	multiset<costs_elem>::iterator it1, it2;
	it1 = it2 = costs.begin();
	while (true) {
		++it2;
		if (it2 == costs.end()) {
			break;
		}
		if (it2->color != it1->color) {
			answers.insert(it2->cost - it1->cost);
		}
		it1 = it2;
	}
}

/*void printCosts() {
	for (multiset<costs_elem>::iterator it=costs.begin(); it!=costs.end(); ++it) {
		printf("(%d,%d,%d)\n",it->cost,it->color,it->index);
	}
	puts("");
}

void printAnswers() {
	printf("{");
	for (multiset<int>::iterator it=answers.begin(); it!=answers.end(); ++it) {
		printf("%d,",*it);
	}
	puts("}");
}*/

void update(int node,int newValue) {
	if (!bipartite) {
		return;
	}
	multiset<costs_elem>::iterator it = costs.find((costs_elem){cost[node],color[node],node});
	if (it != costs.begin()) {
		multiset<costs_elem>::iterator itprev = it; --itprev;
		if (itprev->color != it->color) {
			answers.erase(answers.find(it->cost - itprev->cost));
		}
	}
	multiset<costs_elem>::iterator itnext = it; ++itnext;
	if (itnext != costs.end()) {
		if (itnext->color != it->color) {
			answers.erase(answers.find(itnext->cost - it->cost));
		}
	}

	if (it != costs.begin() && itnext != costs.end()) {
		multiset<costs_elem>::iterator itprev = it; --itprev;
		if (itnext->color != itprev->color) {
			answers.insert(itnext->cost - itprev->cost);
		}
	}

	costs.erase((costs_elem){cost[node],color[node],node});
	cost[node] = newValue;
	costs.insert((costs_elem){cost[node],color[node],node});
	it = costs.find((costs_elem){cost[node],color[node],node});
	if (it != costs.begin()) {
		multiset<costs_elem>::iterator itprev = it; --itprev;
		if (itprev->color != it->color) {
			answers.insert(it->cost - itprev->cost);
		}
	}
	itnext = it; ++itnext;
	if (itnext != costs.end()) {
		if (itnext->color != it->color) {
			answers.insert(itnext->cost - it->cost);
		}
	}

	if (it != costs.begin() && itnext != costs.end()) {
		multiset<costs_elem>::iterator itprev = it; --itprev;
		if (itnext->color != itprev->color) {
			answers.erase(answers.find(itnext->cost - itprev->cost));
		}
	}
	//printCosts();
	//printAnswers();
}

int query(int node1,int node2) {
	if (!bipartite) {
		return 0;
	}
	if (color[node1] == color[node2]) {
		return 0;
	}
	if (answers.size() == 0) {
		return 0;
	}
	return (*(answers.begin()));
}

int main() {
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d",&cost[i]);
	}
	while (m--) {
		scanf("%d %d",&a,&b);
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	memset(color,-1,sizeof(color));
	bipartite = true;
	color[1] = 0;
	dfs(1);
	init();

	scanf("%d",&q);
	while (q--) {
		scanf("%d",&queryType);
		scanf("%d %d",&a,&b);
		if (queryType == 0) { 
			update(a,b);
		} else if (queryType == 1) { 
			printf("%d\n",query(a,b));
		}
	}
	return 0;
}











