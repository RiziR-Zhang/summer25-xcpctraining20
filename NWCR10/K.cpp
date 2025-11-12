#include<bits/stdc++.h>
//#define DEBUG
using namespace std;

const int maxn=1e4+10,M=5e5+10;
int n,m,sum,tim,top,s;
int p[maxn],head[maxn],sd[maxn],dfn[maxn],low[maxn];
int stac[maxn],vis[maxn];
int h[maxn],in[maxn],dist[maxn];
struct EDGE{
	int to;int next;int from;
}edge[maxn+M],ed[maxn+M];
void add(int x,int y){
	edge[++sum].next=head[x];
	edge[sum].from=x;
	edge[sum].to=y;
	head[x]=sum;
}
void tarjan(int x){
	low[x]=dfn[x]=++tim;
	stac[++top]=x;vis[x]=1;
	for (int i=head[x];i;i=edge[i].next){
		int v=edge[i].to;
		if (!dfn[v]) {
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
	    else if (vis[v]){
	    	low[x]=min(low[x],dfn[v]);
		}
	}
	if (dfn[x]==low[x]){
		int y;
		while (y=stac[top--]){
			sd[y]=x;
			vis[y]=0;
			if (x==y) break;
			p[x]+=p[y];
			p[y] = 0;
		}
	}
}
int sz[maxn],d[maxn],rt;
bitset<maxn> arr[maxn];
int sub[maxn], hson[maxn];
void dfs1(int u){
    sub[u] = p[u];
    hson[u] = 0;
    for(int i = h[u]; i; i = ed[i].next){
        int v = ed[i].to;
        dfs1(v);
        sub[u] += sub[v];
        if(!hson[u] || sub[v] > sub[hson[u]]){
            hson[u] = v;
        }
    }
}
void dfs2(int u){
    arr[u].reset();
    arr[u][0] = 1;
    if(hson[u]){
        dfs2(hson[u]);
        arr[u] = arr[hson[u]];
    }
    for(int i = h[u]; i; i = ed[i].next){
        int v = ed[i].to;
        if(v == hson[u]) continue;
        dfs2(v);
        bitset<maxn> base = arr[u];
        for(int pos = 1; pos <= sub[v]; ++pos){
            if(arr[v][pos]){
                arr[u] |= (base << pos);
            }
        }
    }
    arr[u][sub[u]] = 1;
#ifdef DEBUG
cout<<"#"<<u<<'('<<hson[u]<<')'<<endl;
for(int pos = arr[u]._Find_first(); pos != maxn; pos = arr[u]._Find_next(pos)){
    cout<<pos<<' ';
}
cout<<endl;
#endif
}
void solve(){
	cin>>n;
	for (int i=1;i<=n;i++)cin>>p[i];
	for (int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		d[v]++;
	}
	for(int i=1;i<=n;i++){
		if(d[i]==0)rt=i;
	}
	cin>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
	}
	tarjan(rt);
	for (int i=1;i<n+m;i++){
		int x=sd[edge[i].from],y=sd[edge[i].to];
		if (x!=y){
			ed[++s].next=h[x];
			ed[s].to=y;
			ed[s].from=x;
			h[x]=s;
			in[y]++;
		}
	}
    dfs1(rt);
    dfs2(rt);
    int Ans = arr[rt].count();
    std::cout << Ans << endl;
	return;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--)solve();
}