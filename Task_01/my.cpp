// Datatructure homework task_01
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <cstdlib>
using namespace std;
const long long oo = 0x3f3f3f3f3f3f3f3fll;
namespace SPLAY{
	const int max_node = 200005;
#define lson(x) son[(x)][0]
#define rson(x) son[(x)][1]
#define g(x) pre[pre[(x)]]
	template <class Key, class Value> // number, name
	struct Splay{
		int root,tot;
		int pre[max_node];
		int son[max_node][2];

		Key key[max_node];
		Value value[max_node];

		int new_node(){
			tot++;
			pre[tot] = 0;
			son[tot][0] = son[tot][1] = 0;
			return tot;
		}
		void init(Key minx, Key maxx){
			tot = -1;
			new_node(); // remove the node 0;

			root = new_node();
			rson(root) = new_node();
			pre[rson(root)] = root;
			key[root] = minx;
			key[rson(root)] = maxx;
		}
		void rotate(int x){ // 0 left, 1 right
			int y = pre[x], z = pre[y], kind = (x == lson(y));
			son[y][kind^1] = son[x][kind];
			son[x][kind] = pre[son[y][kind^1]] = y;
			pre[y] = x, pre[x] = z;
			if(z) son[z][y == rson(z)] = x;
		}
		void splay(int x,int at){
			while(pre[x] != at){
				if(g(x) == at) { rotate(x); break; }
				int y = pre[x], z = pre[y];
				if((y == lson(z))^(x == lson(y))) { rotate(x); rotate(x);}
				else { rotate(y); rotate(x); }
			}
			if(at == 0) root = x;
		}

		int access_L(Key x, int cur){// return the last node that < x
			while(1){
				if(key[cur] < x){
					if(rson(cur) && key[rson(cur)] < x) cur = rson(cur);
					else return cur;
				} else if(key[cur] >= x){
					if(lson(cur)) cur = lson(cur);
				}
			}
		}
		int access_R(Key x, int cur){// return the first node that > x
			while(1){
				if(key[cur] > x){
					if(lson(cur) && key[lson(cur)] > x) cur = lson(cur);
					else return cur;
				}else if(key[cur] <= x){
					if(rson(cur)) cur = rson(cur);
				}
			}
		}

		void INSERT(Key x,Value w){ 
			int l = access_L(x,root), r = access_R(x,root);
			splay(l,0), splay(r,l);
			key[lson(r)] = x;
			value[lson(r)] = w;
		}
		void DELETE(Key x){ 
			int l = access_L(x,root), r = access_R(x,root);
			splay(l,0), splay(r,l);
			lson(r) = 0;
		}
		bool QUERY(Key x, Value &rev){ // return true/false;
			int l = access_L(x,root), r = access_R(x,root);
			splay(l,0), splay(r,l);
			if(lson(r) == 0) return 0;
			rev = value[lson(r)];
			return 1;
		}
		void dfs(int x){
			if(x == 0) return;
			cout << key[x] << " " << value[x] << endl;
			dfs(lson(x)); dfs(rson(x));
		}

	};
#undef lson
#undef rson
#undef g
}

typedef pair<vector <long long>, string> INFO;

SPLAY::Splay <string, INFO > name2info; // name -> (num, location)
SPLAY::Splay <long long, string> num2name; // num -> name;



int main(){
#ifdef __APPLE__
	freopen("main.in","r",stdin);
#endif
	string maxs; maxs.clear();
	for(int i = 0; i < 1000; i++) maxs += 'z';
	name2info.init("\0", maxs);
	num2name.init(0,oo);

	while(1){
		string op; cin >> op;
		if(op == "Quit"){
			exit(0);
		}else if( op == "Qname" ){
			string name; cin >> name;
			INFO cur; 
			bool isSuccess = name2info.QUERY(name, cur);
			if(isSuccess){
				cout << "Name: " << name << endl;
				for(int i = 0; i < cur.first.size(); i++){
					printf("Phone number %d: %lld\n", i+1, cur.first[i]);
				}
				cout << "Localtion: " << cur.second << endl;
			}else {
				puts("We do not find this person, would you like to add his/her to your phone pad ? [Yes/No]");
			}
		}else if( op == "Qnumber"){
			long long number; cin >> number;
			string name;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				INFO cur; name2info.QUERY(name, cur);
				cout << "Name: " << name << endl;
				cout << "Localtion: " << cur.second << endl;
			}else {
				puts("We do not find this number, please check again.");
			}
		}else if(op == "Cname"){
			string name, new_name;
			long long number;
		       	cin >> number >> new_name;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				INFO cur; name2info.QUERY(name, cur);
				for(int i = 0; i < cur.first.size(); i++) {
					num2name.DELETE(cur.first[i]);
					num2name.INSERT(cur.first[i], new_name);
				}
				name2info.DELETE(name);
				name2info.INSERT(name, cur);
			}else {
				puts("We do not find this number, please check again.");
			}

		} else if(op == "Clocation"){
			string name, new_location;
			long long number;
		       	cin >> number >> new_location;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				INFO cur; name2info.QUERY(name, cur);
				name2info.DELETE(name);
				cur.second = new_location;
				name2info.INSERT(name, cur);
			}else {
				puts("We do not find this number, please check again.");
			}
		} else if(op == "Dperson"){
			long long number;
		       	cin >> number;
			string name;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				INFO cur; name2info.QUERY(name, cur);
				for(int i = 0; i < cur.first.size(); i++) {
					num2name.DELETE(cur.first[i]);
				}
				name2info.DELETE(name);
			}else {
				puts("We do not find this number, please check again.");
			}
		}
		else if( op == "Sort"){
			num2name.dfs(num2name.root);
		} else {
			puts("Please input the right command.");
		}
	}
	return 0;
}
