#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

namespace PQ{
	template <class Type, class Cmp>
	struct PriorityQueue{
		int size, N;
		Cmp cmp;
		Type *w;
		PriorityQueue(){
			w = new Type[10];
			N = 10; size = 0;
		}
		void resize(int nN){
			Type* tmp = new Type[nN];
			for(int i = 1; i <= size; i++)
				tmp[i] = w[i];
			swap(w, tmp), N = nN;
			delete[] tmp;
		}
		void push(Type x){
			if(size+1  == N) resize(2 * N);
			int rt; w[rt = ++size] = x;
			while(rt > 1) {
				if(cmp(w[rt], w[rt>>1])) swap(w[rt], w[rt>>1]), rt >>= 1;
				else break;
			}
		}
		void pop(){
			int rt; w[rt = 1] = w[size--];
			while((rt<<1) <= size){
				int nx = rt<<1;
				if(nx+1 <= size && cmp(w[nx+1], w[nx])) ++nx;
				if(cmp(w[nx], w[rt])) swap(w[nx], w[rt]), rt = nx;
				else break;
			}
			if(size * 4 + 1 < N) resize(N >> 1);
		}
		Type top(){
			return w[1];
		}
		bool empty(){
			return size == 0;
		}
		~PriorityQueue(){
			delete[] w;
		}
	};
};

const int maxn = 105, maxm = maxn * maxn;
const int oo = 0x3f3f3f3f;

struct Data{
	int tov, next, val;
}data[maxm];
int head[maxn], tot;

void insert(int a, int b, int w){
	tot++;
	data[tot].tov = b;
	data[tot].val = w;
	data[tot].next = head[a];
	head[a] = tot;
}

int dis[maxn];
int pre[maxn];
typedef pair<int, int> pii;
// first id
// second distance
struct cmp{
	bool operator () (const pii &a, const pii &b){
		return a.second < b.second;
	}
};

void printRoute(int x){
	if(x == 1) { printf("%d -> ", x); return; }
	printRoute(pre[x]); printf("%d -> ", x);
}

void getAccessTalbe(int n){
	PQ::PriorityQueue <pii, cmp> q;
	memset(dis, 0x3f, sizeof(dis));
	q.push(pii(1, 0));
	while(!q.empty()){
		pii tt = q.top(); q.pop();
		if(tt.second > dis[tt.first]) continue;
		for(int k = head[tt.first]; k; k = data[k].next){
			int w = data[k].tov;
			if(dis[w] > tt.second + data[k].val){
				pre[w] = tt.first;
				dis[w] = tt.second + data[k].val;
				q.push(pii(w, dis[w]));
			}
		}
	}
	for(int i = 2; i <= n; i++) {
		printf("%d: ", i);
		if(dis[i] != oo){
			printRoute(i); 
			printf("\b\b\b| distance: %dms\n", dis[i]);
		}else {
			puts("oo");
		}
	}
}

int randint(int l, int r){
	int del = r - l + 1;
	return rand() % del + l;
}

void RDMshuffle(int *w, int n){ // random shuffle
	for(int i = 1; i <= n; i++){
		int j = randint(i, n);
		swap(w[i], w[j]);
	}
}

void updateAccessInfo(int n){ // n个结点的网络(包括网关)
	memset(head, 0, sizeof(head)); tot = 0;
	int tmp[maxn], cnt;
	for(int i = 1; i <= n; i++){
		printf("info %d:\n", i);
		memset(tmp, 0, sizeof(tmp)); cnt = 0;
		int neighborNum = randint(0, n-1); //一个点不能和自己相连
		for(int j = 1; j <= n; j++) if(i != j) tmp[++cnt] = j;
		RDMshuffle(tmp, cnt);
		for(int j = 1; j <= neighborNum; j++){
			int val = randint(0, 100);
			insert(i, tmp[j], val); //加边
			printf("%d -> %d %dms\n", i, tmp[j], val);
		}
		puts("");
	}
}

void mainLoop(int n){
	int t = 10;
	while(t--){
		//getchar(); // pause
		updateAccessInfo(n); puts("");
		getAccessTalbe(n);
	}
}

int main(){
	//srand(time(NULL));
	int n; scanf(" %d", &n);
	mainLoop(n);
	return 0;
}
