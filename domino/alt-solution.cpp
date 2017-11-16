// Second solution by Winardi Kurniawan

#include<stdio.h>
#include<map>
#include<algorithm>

struct dt{
	int u;
	int v;
	int w;
};

bool compare(struct dt a, struct dt b){
	if(a.w < b.w){
		return true;
	}
	return false;
}

using namespace std;

dt data[100010];

int main(){
	map<int, int> mp;
	int nt, n, b, first, second;

	scanf("%d %d", &n, &b);
	
	mp.clear();
	int res = 0;
	for(int i=0; i<n; i++){
		scanf("%d %d %d", &data[i].u, &data[i].v, &data[i].w);
	}
	sort(data, data+n, compare);

	for(int i=0; i<n; i++){
		int first = data[i].u;
		int second = data[i].v;
		if(mp[first] == 0){
			res++;
			mp[first] += b-1;
		}
		else{
			mp[first]--;
		}
		mp[second] += b;

	}

	printf("%d\n", res);

	return 0;
}