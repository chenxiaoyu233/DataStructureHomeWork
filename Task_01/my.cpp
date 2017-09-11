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
		Key maxx[max_node];
		Key minn[max_node];
		Value value[max_node];

		Key _MIN_, _MAX_;

		int new_node(){
			tot++;
			pre[tot] = 0;
			son[tot][0] = son[tot][1] = 0;
			return tot;
		}
		//Key min(Key a, Key b){ return a < b ? a : b;}
		//Key max(Key a, Key b){ return a > b ? a : b;}
		void push_up(int x){
			maxx[x] = minn[x] = key[x];
			if(lson(x)){
				maxx[x] = max(maxx[x],maxx[lson(x)]);
				minn[x] = min(minn[x],minn[lson(x)]);
			}
			if(rson(x)){
				maxx[x] = max(maxx[x],maxx[rson(x)]);
				minn[x] = min(minn[x],minn[rson(x)]);
			}
		}
		void init(Key minx_, Key maxx_){
			_MIN_ = minx_;
			_MAX_ = maxx_;
			tot = -1;
			new_node(); // remove the node 0;

			root = new_node();
			rson(root) = new_node();
			pre[rson(root)] = root;

			key[root] = minx_;
			maxx[root] = minn[root] = minx_;
			key[rson(root)] = maxx_;
			maxx[rson(root)] = minn[rson(root)] = maxx_;
			push_up(root);
		}
		void rotate(int x){ // 0 left, 1 right
			int y = pre[x], z = pre[y], kind = (x == lson(y));
			son[y][kind^1] = son[x][kind];
			son[x][kind] = pre[son[y][kind^1]] = y;
			pre[y] = x, pre[x] = z;
			if(z) son[z][y == rson(z)] = x;
			push_up(y);
		}
		void splay(int x,int at){
			while(pre[x] != at){
				if(g(x) == at) { rotate(x); break; }
				int y = pre[x], z = pre[y];
				if((y == lson(z))^(x == lson(y))) { rotate(x); rotate(x);}
				else { rotate(y); rotate(x); }
			}
			push_up(x);
			if(at == 0) root = x;
		}

		int access_L(Key x, int cur){// return the last node that < x
			while(1){
				if(key[cur] >= x && lson(cur)) cur = lson(cur);
				else if(rson(cur) && minn[rson(cur)] < x) cur = rson(cur);
				else return cur;
			}
		}
		int access_R(Key x, int cur){// return the first node that > x
			while(1){
				if(key[cur] <= x && rson(cur)) cur = rson(cur);
				else if(lson(cur) && maxx[lson(cur)] > x) cur = lson(cur);
				else return cur;
			}
		}

		void INSERT(Key x,Value w){ 
			int l = access_L(x,root), r = access_R(x,root);
			splay(l,0), splay(r,l);
			lson(r) = new_node();
			pre[lson(r)] = r;
			key[lson(r)] = minn[lson(r)] = maxx[lson(r)] = x;
			value[lson(r)] = w;
			push_up(r), push_up(l);
		}
		void DELETE(Key x){ 
			int l = access_L(x,root), r = access_R(x,root);
			splay(l,0), splay(r,l);
			lson(r) = 0;
			push_up(r), push_up(l);
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

			dfs(lson(x));
			if(key[x] != _MIN_ && key[x] != _MAX_) cout << key[x] << " " << value[x] << endl;
			dfs(rson(x));
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
/*#ifdef __APPLE__
	freopen("main.in","r",stdin);
#endif*/
	string maxs; maxs.clear();
	for(int i = 0; i < 1000; i++) maxs += 'z';
	name2info.init("\0", maxs);
	num2name.init(0,oo);

	while(1){
		printf("~$ ");
		string op; cin >> op;
		//system("clear");
		if(op == "Quit"){
			exit(0);
		}else if( op == "Qname" ){
			puts("-----------------------------------------------------");
			puts("Please input the name");
			puts("-----------------------------------------------------");
			printf("~$ ");
			string name; cin >> name;
			INFO cur; 
			bool isSuccess = name2info.QUERY(name, cur);
			if(isSuccess){
				puts("-----------------------------------------------------");
				cout << "Name: " << name << endl;
				for(int i = 0; i < cur.first.size(); i++){
					printf("Phone number %d: %lld\n", i+1, cur.first[i]);
				}
				cout << "Localtion: " << cur.second << endl;
				puts("-----------------------------------------------------");
			}else {
				puts("--------------------------------------------------------------------------------------");
				puts("We do not find this person, would you like to add he/her to your phone pad ? [Yes/No]");
				puts("--------------------------------------------------------------------------------------");
				printf("~$ ");
				cin >> op;
				if(op == "Yes"){
					puts("-----------------------------------------------------");
					puts("Please input the number of his/her phone number");
					puts("-----------------------------------------------------");
					printf("~$ ");
					int n; cin >> n;
					puts("-----------------------------------------------------");
					puts("Please input these these phone number");
					puts("-----------------------------------------------------");
					vector <long long> now; now.clear();
					for(int i = 1; i <= n; i++) {
						long long a;
						printf("~$ ");
						cin >> a;  now.push_back(a);
						num2name.INSERT(a,name);
					}
					puts("-----------------------------------------------------");
					puts("Please input his/her location");
					puts("-----------------------------------------------------");
					printf("~$ ");
					string lo; cin >> lo;
					name2info.INSERT(name,make_pair(now,lo));
					puts("-----------------------------------------------------");
					puts("added");
					puts("-----------------------------------------------------");
				}
			}
		}else if( op == "Qnumber"){
			puts("-----------------------------------------------------");
			puts("Please input the number");
			puts("-----------------------------------------------------");
			printf("~$ ");
			long long number; cin >> number;
			string name;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				puts("-----------------------------------------------------");
				INFO cur; name2info.QUERY(name, cur);
				cout << "Name: " << name << endl;
				cout << "Localtion: " << cur.second << endl;
				puts("-----------------------------------------------------");
			}else {
				puts("-----------------------------------------------------");
				puts("We do not find this number, please check again.");
				puts("-----------------------------------------------------");
			}
		}else if(op == "Cname"){
			string name, new_name;
			long long number;
			puts("-----------------------------------------------------");
			puts("Please input the phone number and the new name");
			puts("-----------------------------------------------------");
			printf("~$ ");
			cin >> number >> new_name;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				INFO cur; name2info.QUERY(name, cur);
				for(int i = 0; i < cur.first.size(); i++) {
					num2name.DELETE(cur.first[i]);
					num2name.INSERT(cur.first[i], new_name);
				}
				name2info.DELETE(name);
				name2info.INSERT(new_name, cur);
				puts("-----------------------------------------------------");
				puts("Change complete");
				puts("-----------------------------------------------------");
			}else {
				puts("-----------------------------------------------------");
				puts("We do not find this number, please check again.");
				puts("-----------------------------------------------------");
			}

		} else if(op == "Clocation"){
			string name, new_location;
			long long number;
			puts("-----------------------------------------------------");
			puts("Please input the phone number and the new location");
			puts("-----------------------------------------------------");
			printf("~$ ");
			cin >> number >> new_location;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				INFO cur; name2info.QUERY(name, cur);
				name2info.DELETE(name);
				cur.second = new_location;
				name2info.INSERT(name, cur);
				puts("-----------------------------------------------------");
				puts("Change complete");
				puts("-----------------------------------------------------");
			}else {
				puts("-----------------------------------------------------");
				puts("We do not find this number, please check again.");
				puts("-----------------------------------------------------");
			}
		} else if(op == "Dperson"){
			long long number;
			puts("-----------------------------------------------------");
			puts("Please input the phone number");
			puts("-----------------------------------------------------");
			printf("~$ ");
			cin >> number;
			string name;
			bool isSuccess = num2name.QUERY(number, name);
			if(isSuccess){
				INFO cur; name2info.QUERY(name, cur);
				for(int i = 0; i < cur.first.size(); i++) {
					num2name.DELETE(cur.first[i]);
				}
				name2info.DELETE(name);
				puts("-----------------------------------------------------");
				puts("Delete complete");
				puts("-----------------------------------------------------");
			}else {
				puts("-----------------------------------------------------");
				puts("We do not find this number, please check again.");
				puts("-----------------------------------------------------");
			}
		}
		else if( op == "Sort"){
			puts("-----------------------------------------------------");
			num2name.dfs(num2name.root);
			puts("-----------------------------------------------------");
		} else if( op == "Help"){
			puts("--------------------------------------------------------------------------------------------------------");
			printf( "Qname :     Query by name\n"
				"Qnumber :   Query by number\n"
				"Cname :     Change a persons name by number\n"
				"Clocation : Change a persons location by number\n"
				"Dperson :   Delete a person by number\n"
				"Sort :      Sort the people by their number (one person may by printed many times if he/she has many numbers\n"
				"Quit :      Exit the program\n");
			puts("--------------------------------------------------------------------------------------------------------");
		} else {
			puts("-----------------------------------------------------");
			puts("Please input the right command.");
			puts("-----------------------------------------------------");
		}
	}
	return 0;
}
