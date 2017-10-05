#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#define FOR(i, l, r) for(int (i) = (l); (i) <= (r); (i)++)
using namespace std;
const int maxn = 1005;
int n,m;
inline int randint(int l,int r){ // r - l <= 1e5
	int del = r - l + 1;
	return rand()%del + l;
}
int fa[maxn * maxn];
int find(int x){
	if(x == fa[x]) return x;
	return fa[x] = find(fa[x]);
}
char w[maxn][maxn];
int dirx[] = {0,0,2,-2};
int diry[] = {2,-2,0,0};
struct Point{
	int x,y;
	Point(int x = 0, int y = 0): x(x), y(y){}
	friend bool operator < (const Point &a, const Point &b){
		if(a.x == b.x) return a.y < b.y;
		return a.x < b.x;
	}
	friend Point operator + (const Point &a, const Point &b){
		return Point(a.x + b.x, a.y + b.y);
	}
	friend Point operator / (const Point &a, int b){
		return Point(a.x / b, a.y / b);
	}
};
struct Edge{
	Point from, to;
	Edge(Point from, Point to): from(from), to(to){}
};
vector <Edge> edges;
void show(){
	FOR(i, 0, n+1) printf("%s\n", w[i]);
}
int to[maxn][maxn];
int tot;
inline int Get(Point a){
	int x = a.x, y = a.y;
	if(!to[x][y])
		to[x][y] = ++tot;
	return to[x][y];
}
int main(){
#ifdef __APPLE__
	freopen("main.in","w",stdout);
#endif
	srand(time(NULL));
	n = randint(10, 20), m = randint(10, 20);
	n += !(n&1), m += !(m&1);
	printf("%d %d\n", n+2, m+2);
	for(int i = 1, s = n * m; i <= s; i++) fa[i] = i;
	FOR(i, 1, n) FOR(j, 1, m) w[i][j] = '#';
	for(int i = 1; i <= n; i += 2) 
		for(int j = 1; j <= m; j += 2){
			w[i][j] = '.';
			FOR(k, 0, 3){
				int x1 = i + dirx[k], y1 = j + diry[k];
				if(x1 < 1 || x1 > n || y1 < 1 || y1 > m) continue;
				if(Point(x1, y1) < Point(i, j))
				       	edges.push_back(Edge(Point(i, j), Point(x1, y1)));
			}
		}
	for(int i = 0; i < edges.size(); i++){
		swap(edges[i], edges[randint(i,edges.size()-1)]);
	}
	for(int i = 0; i < edges.size(); i++){
		int fx = find(Get(edges[i].from));
		int fy = find(Get(edges[i].to));
		if(fx != fy){
			fa[fx] = fy;
			Point mid = (edges[i].from + edges[i].to) / 2;
			w[mid.x][mid.y] = '.';
		}
	}
	FOR(i, 0, n+1) w[i][0] = w[i][m+1] = '#';
	FOR(j, 0, m+1) w[0][j] = w[n+1][j] = '#';

	for(int i = 1; i <= 3; i++) {
		w[randint(1,n)][randint(1,m)] = 's';
	}
	for(int i = 1; i <= 3; i++) {
		w[randint(1,n)][randint(1,m)] = 't';
	}
	show();
	return 0;
}
