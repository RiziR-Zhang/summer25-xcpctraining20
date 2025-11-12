#include <bits/stdc++.h>
#define rep(i,n) for(int i=0,del##i##verme=int(n);i<del##i##verme;++i)
#define rep1(i,n) for(int i=1,parano##i##a=int(n);i<=parano##i##a;++i)
#define per(i,n) for(int i=int(n)-1;i>=0;--i)
#define per1(i,n) for(int i=int(n);i>=1;--i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define y0 LingLuo
#define y1 VividCycle
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
using namespace std;
const ll mod1=998244353;
const ll mod2=1000000007;
unsigned time_related_rand()
{
	return unsigned(std::chrono::steady_clock::now().time_since_epoch().count());
}
int n,u,v,a[200005],b[200005];
struct dsu{
	int p[400005],d[400005],ds[400005],s[400005];// parent, degree(mod 2) of self/comp, is singlet
	int c,cc,c1;// count of singlets, connected components of ds=0, odd-degreed points
	void init()
	{
		rep1(i,400000)
		{
			p[i]=i;d[i]=0;ds[i]=0;s[i]=1;
		}
		c=cc=400000;c1=0;
	}
	void clear()
	{
		c=cc=400000;c1=0;
	}
	void clear(int x)
	{
		p[x]=x;d[x]=0;ds[x]=0;s[x]=1;
	}
	int answer()
	{
		return c1/2+cc-c;
	}
	int getp(int x)
	{
		return (p[x]==x)?x:(p[x]=getp(p[x]));
	}
	void merge(int x,int y)
	{
		int dx=2*(d[x]^=1)-1;
		int dy=2*(d[y]^=1)-1;
		c1+=dx+dy;
		c-=s[x];s[x]=0;c-=s[y];s[y]=0;
		x=getp(x);y=getp(y);
		if(x==y)
		{
			cc-=(ds[x]==0);
			ds[x]+=dx+dy;
			cc+=(ds[x]==0);
			return ;
		}
		cc-=(ds[x]==0);cc-=(ds[y]==0);
		ds[y]+=ds[x]+dx+dy;cc+=(ds[y]==0);p[x]=y;
	}
};
dsu D;
vector<int> con[200005];
int siz[200005],heavy[200005],ans[200005];
void dfs(int ver,int par)
{
	siz[ver]=1;for(int x:con[ver])if(x!=par){dfs(x,ver);if(siz[x]>siz[heavy[ver]])heavy[ver]=x;
	siz[ver]+=siz[x];}
}
void add_subtree(int ver,int par)
{
	D.merge(a[ver],b[ver]);
	for(int x:con[ver])if(x!=par)add_subtree(x,ver);
}
void clear_inner(int ver,int par)
{
	D.clear(a[ver]);D.clear(b[ver]);
	for(int x:con[ver])if(x!=par)clear_inner(x,ver);
}
void clear_subtree(int ver,int par)
{
	D.clear();
	clear_inner(ver,par);
}
void solve(int ver,int par)
{
	if(heavy[ver]==0)
	{
		D.merge(a[ver],b[ver]);
		ans[ver]=D.answer();
		return ;
	}
	for(int x:con[ver])if(x!=par&&x!=heavy[ver]){solve(x,ver);clear_subtree(x,ver);}
	solve(heavy[ver],ver);
	D.merge(a[ver],b[ver]);
	for(int x:con[ver])if(x!=par&&x!=heavy[ver])add_subtree(x,ver);
	ans[ver]=D.answer();
//    clear_subtree(ver, par);
}
//#define FILE
int main()
{
	ios_base::sync_with_stdio(false);cin.tie(0);
#ifdef FILE
freopen("A.in","r",stdin);
freopen("Aac.out","w",stdout);
int tsk;
cin>>tsk;
while(tsk--){
#endif
	cin>>n;
	rep1(i,n) cin>>a[i];
	rep1(i,n) cin>>b[i];
	D.init();
	rep1(i,n-1)
	{
		cin>>u>>v;con[u].pb(v);con[v].pb(u);
	}
	dfs(1,0);
	solve(1,0);
    clear_subtree(1,0);
	rep1(i,n)
	{
		cout<<ans[i]<<" ";
	}
    cout<<endl;
#ifdef FILE
rep1(i,n) con[i].clear(), heavy[i] = 0;
}
fclose(stdin);fclose(stdout);
#endif
	return 0;
}
/* things to check
1.  int overflow or long long memory need
2.  recursion/array/binary search/dp/loop bounds
3.  precision
4.  special cases(n=1,bounds)
5.  delete debug statements
6.  initialize(especially multi-tests)
7.  = or == , n or m ,++ or -- , i or j , > or >= , < or <=
8.  keep it simple and stupid
9.  do not delete, use // instead
10. operator priority
11. is there anything extra to output?
12. ...
*/

/* something to think about
1. greedy? dp? searching? dp with matrix/ segment tree? binary search?
2. If contains "not", why not ?????? or few affect?
*/
