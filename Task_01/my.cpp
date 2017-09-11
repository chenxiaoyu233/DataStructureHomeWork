/*
 * splay 模板 v1.0
 * 使用时记得在一头一尾加上虚点。
 */
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
namespace SPLAY{
	const int max_node = 200005;
	const int oo = 0x3f3f3f3f;
#define lson(x) son[(x)][0]
#define rson(x) son[(x)][1]
#define g(x) pre[pre[(x)]]
	template <class Key, class Value> // number, name
	struct Splay{
		int root,tot;
		int pre[max_node];
		int son[max_node][2];
		int size[max_node]; // the size of the subtree

		Key key[max_node];
		Value value[max_node];

		int new_node(){
			tot++;
			pre[tot] = 0;
			son[tot][0] = son[tot][1] = 0;
			return tot;
		}
		void init(){
			tot = -1;
			root = new_node();
		}
		void push_down(int x){
			if(x == 0) return;
			/*
			 *
			 */
		}
		void push_up(int x){
			if(x == 0) return;
			size[x] = size[lson(x)] + size[rson(x)] + 1;
			/*
			 *
			 */
		}
		void rotate(int x){ // 0 left, 1 right
			int y = pre[x], z = pre[y], kind = (x == lson(y));
			push_down(y), push_down(x); // push_down
			son[y][kind^1] = son[x][kind];
			son[x][kind] = pre[son[y][kind^1]] = y;
			pre[y] = x, pre[x] = z;
			if(z) son[z][y == rson(z)] = x;
			push_up(y); // push_up
		}
		void splay(int x,int at){
			push_down(x); // push_down
			while(pre[x] != at){
				if(g(x) == at) { rotate(x); break; }
				int y = pre[x], z = pre[y];
				if((y == lson(z))^(x == lson(y))) { rotate(x); rotate(x);}
				else { rotate(y); rotate(x); }
			}
			push_up(x); // push_up
			if(at == 0) root = x;
		}
		int access(Key x, int cur){// return the last node that <= x
			while(1){
				if(lson(cur) && x < key[lson(cur)]) cur = lson(cur);
				else if(rson(cur) && key[rson(cur)] <= x)  cur = rson(cur);
				else return cur;
			}
		}
		int get_min(int cur){
		}

		void INSERT(Key x,Value w){ 
		}
		void DELETE(int x){ 
		}
	};
#undef lson
#undef rson
#undef g
}

SPLAY::Splay <string, vector<long long> > name2info;
SPLAY::Splay <int, string> num2name;


int main(){
#ifdef __APPLE__
	freopen("main.in","r",stdin);
#endif
	return 0;
}
