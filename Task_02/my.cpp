#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#include <utility>
#define FOR(i,l,r) for(int (i) = (l); (i) <= (r); (i)++)
using namespace std;
typedef pair<int,int> pii;
const int oo = 0x3f3f3f3f;
const int maxn = 1005;
int n,m;
char w[maxn][maxn];

int dirx[]={0,0,1,-1};
int diry[]={1,-1,0,0};
void init(){
	scanf(" %d%d", &n, &m);
	FOR(i, 1, n) FOR(j, 1, m) scanf(" %c", w[i] + j);
}
#define x first
#define y second
int dis[maxn][maxn];
pii pre[maxn][maxn];
inline void print_ans(pii at){
	printf("Mininum distance is: %d\n", dis[at.x][at.y]);
	while(w[at.x][at.y] != 's'){
		w[at.x][at.y] = '@';
		at = pre[at.x][at.y];
	} w[at.x][at.y] = '@';
	printf("The path is as follow:\n");
	FOR(i, 1, n) printf("%s\n", w[i] + 1);
}
inline void bfs(){
	queue <pii> q;
	memset(dis,0x3f,sizeof(dis));
	FOR(i, 1, n) FOR(j, 1, m) if(w[i][j] == 's'){
		q.push(pii(i,j));
		dis[i][j] = 0;
	}
	while(!q.empty()){
		pii tt = q.front(); q.pop();
		if(w[tt.x][tt.y] == 't'){
			print_ans(tt);
			return;
		}
		FOR(i,0,3){
			int x1 = tt.x + dirx[i], y1 = tt.y + diry[i];
			if(x1 < 1 || x1 > n || y1 < 1 || y1 > m) continue;
			if(w[x1][y1] == '#') continue;
			if(dis[x1][y1] == oo){
				q.push(pii(x1,y1));
				pre[x1][y1] = tt;
				dis[x1][y1] = dis[tt.x][tt.y] + 1;
			}
		}
	}
#undef x
#undef y
}
int main(){
#ifdef __APPLE__
	freopen("main.in", "r", stdin);
#endif
	init();
	bfs();
	return 0;
}
