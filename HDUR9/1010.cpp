#include<bits/stdc++.h>
using namespace std;

const int maxn=5e5+10,M=3e6+10;
typedef long long ll;
int n,m,sum,tim,top,s;
int p[maxn],head[maxn],sd[maxn],dfn[maxn],low[maxn];
int stac[maxn],vis[maxn];
int h[maxn],in[maxn],cir[maxn],a[maxn];
struct EDGE{
	int to;int next;int from;
}edge[M],ed[M];
void add(int x,int y){
	edge[++sum].next=head[x];
	edge[sum].from=x;
	edge[sum].to=y;
	head[x]=sum;
}
void tarjan(int x){
	//cout<<x<<'\n';
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
			cir[x]+=1;
			if (x==y) break;
			p[x]+=p[y];
			p[y] = -1;
		}
	}
}	
int ans[maxn];
struct node{
	int x,sum;
	bool rol;
};
void topo(){
	queue<node > q;
	for(int i=1;i<=n;i++){
		if(i==sd[i] && in[i]==0){
			node u;
			u.x=i;
			u.sum=p[i];
            ans[i] = (cir[i] > 1 && p[i] > 0);
            if(ans[i]){
                u.rol = 1;
            }else{
                u.rol = 0;
            }
            q.push(u);
			// if(cir[i]>1){//     i: cir, ans, p
			// 	u.rol=1;//node: x, rol,    , sum
			// 	ans[i]=1;
			// }
			// else {
			// 	u.rol=0;
			// }
			// q.push(u);
		}
	}
	while(!q.empty()){
		node u=q.front();
		q.pop();
        for(int i = h[u.x]; i; i = ed[i].next){
            int v = ed[i].to;
            in[v]--;
            p[v] += u.sum;
            ans[v] |= (cir[v] > 1 && p[v] > 0) || u.rol;
            if(in[v] == 0){
                node t;
                t.x = v;
                t.sum = p[v];
                t.rol = ans[v];
                q.push(t);
            }
        }
		// for(int i=h[u.x];i;i=ed[i].next){
		// 	int v=ed[i].to;
		// 	in[v]--;
		// 	node t;
		// 	t.x=v;
		// 	t.sum=u.sum+p[v];//?
		// 	if(cir[v]>1)t.rol=1;
		// 	if(in[v]==0)q.push(t);
		// 	if(cir[v]>1 && (p[v]!=0 || u.sum!=0)){//?
		// 		ans[v]=1;
		// 	}
		// 	if(u.rol==1 && u.sum!=0)ans[v]=1;
		// }
	}
}
int b[maxn];
void solve(){
	m=0;
	sum=0;
	s=0;
	tim=0;
	top=0;
	memset(cir,0,sizeof(cir));
	memset(in,0,sizeof(in));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(h,0,sizeof(h));
	memset(edge,0,sizeof(edge));
	memset(head,0,sizeof(head));
	memset(ed,0,sizeof(ed));
	cin>>n;
	for (int i=1;i<=n;i++)cin>>a[i],p[i]=a[i];
	for(int i=1;i<=n;i++)cin>>b[i],m+=b[i];
	for(int i=1;i<=n;i++)
		while(b[i]--){
			int x;
			cin>>x;
			add(i,x);
		}
	
	for(int i=1;i<=n;i++){
		if(!dfn[i])tarjan(i);
	}
	for (int i=1;i<=m;i++){
		int x=sd[edge[i].from],y=sd[edge[i].to];
		if (x!=y){
			ed[++s].next=h[x];
			ed[s].to=y;
			ed[s].from=x;
			h[x]=s;
			in[y]++;
		}
	}
	topo();
	int res=0;
	for(int i=1;i<=n;i++){
		if(ans[i]!=0){
			ans[i]=0;
			res+=cir[i];
		}
	}
	cout<<res<<endl;
	return;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)solve();
}