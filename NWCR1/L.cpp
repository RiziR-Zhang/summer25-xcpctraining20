#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<random>
#define Rep(i,a,b) for(int i=(a);i<=(b);++i)
//#define FILE
using namespace std;
constexpr int mN=400005;
typedef long long LL;
mt19937 mrand(998244353);
//pii operator -(pii n1,int n2)
template<typename T>
class FHQTreap{
	private:
		int root,tn;
		struct Nd{
			T val;int rnd,ls,rs,sz;
			Nd(){}
			Nd(T V):val(V),rnd(mrand()),ls(0),rs(0),sz(1){}
		}a[mN];
		inline void upd(int p){a[p].sz=a[a[p].ls].sz+a[a[p].rs].sz+1;}
		void SplitVL(int p,T v,int &lb,int &rb){
			if(!p){lb=0,rb=0;return;}
			if(a[p].val<=v){
				lb=p;
				SplitVL(a[p].rs,v,a[p].rs,rb);//ls->rs
			}else{
				rb=p;
				SplitVL(a[p].ls,v,lb,a[p].ls);
			}
			upd(p);
		}
		int Merge(int x,int y){
			if(x==0||y==0) return x|y;//null->now
			if(a[x].rnd>a[y].rnd){
				a[x].rs=Merge(a[x].rs,y);
				upd(x);
				return x;
			}else{
				a[y].ls=Merge(x,a[y].ls);
				upd(y);
				return y;
			}
		}
	public:
		FHQTreap():root(0),tn(0){}
		void ins(T v){
			a[++tn]=Nd(v);
			int x,y;
			SplitVL(root,v,x,y);
			x=Merge(x,tn);
			root=Merge(x,y);//tn->x
		}
		bool del(T v){
			int x,y,z;
			SplitVL(root,v,x,y);
			SplitVL(x,v-1,x,z);
			bool exs=(z!=0);
			z=Merge(a[z].ls,a[z].rs);//ifa->!ifa,followed
			x=Merge(x,z);
			root=Merge(x,y);
			return exs;
		}
		T kthval(int k){
			int p=root;
			while(p){
				if(a[a[p].ls].sz+1==k) break;
				if(a[a[p].ls].sz+1<k)
					k-=a[a[p].ls].sz+1,p=a[p].rs;
				else
					p=a[p].ls;
			}
			return a[p].val;
		}
		void assn(T &src, T inc){
			int x, y, z;
			SplitVL(root, src, x, y);
			SplitVL(x, src - 1, x, z);
			int w = Merge(a[z].ls, a[z].rs);
			src += inc;
			a[z] = Nd(src);
			int u, v;
			SplitVL(y, src, u, v);
			u = Merge(u, z);
			root = Merge(Merge(x, z), Merge(u, v));
		}
        int lsize(T v){
            int x, y;
            SplitVL(root, v, x, y);
            int ret = a[x].sz;
            root = Merge(x, y);
            return ret;
        }
/*		T solve(){
			int k = (n + 1) / 2 + 1;
			LL val = kthval(k);
			cout<<lsize(val - 1)<<endl;
		}*/
        void reset(){
            tn = root = 0;
        }
};
FHQTreap<LL> tr;
int n;
LL a[mN];
int main()
{
#ifdef FILE
	freopen("L.in","r",stdin);
    freopen("L.out","w",stdout);
#endif
	//srand(20250715);
    ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int tsk, Q;
    cin>>tsk;
    while(tsk--){
        cin>>n>>Q;
        Rep(i, 1, n){
            cin>>a[i];
            tr.ins(a[i]);
        }
        int p, m = (n + 1) / 2 + 1;
        LL v;
        while(Q--){
            cin>>p>>v;
//			tr.assn(a[p], v);
            tr.del(a[p]);
            a[p] += v;
            tr.ins(a[p]);
            //cout<<tr.solve()<<endl;
			LL val = tr.kthval(m);
        	cout<<tr.lsize(val - 1)<<'\n';
        }
        tr.reset();
    }
#ifdef FILE
	fclose(stdin);fclose(stdout);
#endif
	return 0;
}
