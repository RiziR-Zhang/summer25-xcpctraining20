#include<iostream>
#include<cstring>
#include<cstdio>

const int INF = 0x3f3f3f3f;
const int N = 2e5 + 5;

struct edge{
    int nxt,to;
};
edge e[N << 1];
int head[N],cnt;

void add_edge(int u,int v){
    e[++cnt] = {head[u],v};
    head[u] = cnt;
}
struct ST
{
    int st[N << 2];
    void build(int p,int l,int r){
        if(l == r){
            st[p] = -INF;
            return;
        }
        int mid = l + r >> 1;
        build(p << 1,l,mid);
        build(p<<1|1,mid+1,r);
        st[p] = -INF;
    }
    void change(int p,int l,int r,int k,int x){
        if(l == r){
            st[p] = std::max(st[p],x);
            return; 
        }
        int mid = l + r >> 1;
        if(k < mid)
            change(p << 1,l,mid,k,x);
        else
            change(p<<1|1,mid+1,r,k,x);
        st[p] = std::max(st[p<<1],st[p<<1|1]);
    }
    int query(int p,int l,int r,int L,int R){
        if(L <= l && r <= R){
            return st[p];
        }
        int mid = l + r >> 1;
        int res = -INF;
        if(L <= mid)
            res = std::max(res,query(p<<1,l,mid,L,R));
        if(R > mid)
            res = std::max(res,query(p<<1,mid+1,r,L,R));
        return res;
    }
};
ST s1,s2;

int fa[N],dep[N],siz[N],son[N],top[N],dfn[N],rnk[N],tot;
int vis[N];
int p1[N],p2[N],dis[N];
int p[N],rt;
int n,ans;
void dfs1(int u){
    son[u] = 0;
    siz[u] = 1;
    for(int i = head[u];i;i=e[i].nxt){
        int v = e[i].to;
        if(v == fa[u])continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dfs1(v);
        siz[u] += siz[v];
        if(!son[u] || siz[v] > siz[son[u]])son[u] = v;
    }
}
void dfs2(int u,int t){
    top[u] = t;
    dfn[u] = ++tot;
    rnk[tot] = u;
    if(!son[u])return;
    dfs2(son[u],t);
    for(int i = head[u];i;i=e[i].nxt){
        int v = e[i].to;
        if(v == son[u] || v == fa[u])continue;
        dfs2(v,v);
    }
}

void init(){
    memset(dis,0,sizeof(int) * (n + 1));
    memset(p1,0,sizeof(int) * (n + 1));
    memset(p2,0,sizeof(int) * (n + 1));
    memset(head,0,sizeof(int) * (n + 1));
    memset(vis,0,sizeof(int) * (n + 1));
    cnt = tot = 0;
}

int main(){
    int Tsk;
    scanf("%d",&Tsk);
    while(Tsk--){
        scanf("%d",&n);
        init();
        for(int i = 1;i <= n;++i){
            int x;
            scanf("%d",&x);
            p[x] = i;
        }
        for(int i = 1;i < n;++i){
            int x,y;
            scanf("%d%d",&x,&y);
            add_edge(x,y);
            add_edge(y,x);
        }
        rt = p[0];
        fa[rt] = dep[rt] = 0;
        dfs1(rt);
        dfs2(rt,rt);
        vis[rt] = 1;
        ans = 0;
        printf("%d\n",ans);
        s1.build(1,1,n);
        s2.build(1,1,n);
        for(int i = 1;i < n;++i){
            int u = p[i],x = p[i];
            s2.change(1,1,n,dfn[x],dep[x]);
            if(!vis[u]){
/*                while(!vis[u]){
                    vis[u] = 1;
                    u = fa[u];
                }*/
                //printf("---------------\n");
                while(u){
                    if(top[u] != u){
                        ans = std::max(ans,dep[x] + s1.query(1,1,n,dfn[top[u]],dfn[u]));
                        if(son[u]){
                            int v = son[u];
                            ans = std::max(ans,dep[x] + s2.query(1,1,n,dfn[v],dfn[v] + siz[v] - 1) - dep[u] * 2);
                        }
                        u = top[u];
                    }
                    else{
                        int v = fa[u];
                        if(!v)break;
                        dis[u] = std::max(dis[u],dep[x] - dep[v]);
                        if(dis[u] > dis[p1[v]] && u != p1[v]){
                            p2[v] = p1[v];
                            p1[v] = u;
                        }
                        else if(dis[u] > dis[p2[v]] && u != p2[v])
                            p2[v] = u;
                        ans = std::max(ans,dis[p1[v]] + dis[p2[v]]);
                        u = v;
                        s1.change(1,1,n,dfn[u],dep[x] - dep[u] * 2);
                    }
                }
                //printf("u:%d %d\n",x,dep[x]);
                ans = std::max(ans,dep[x]);
            }
            printf("%d\n",(ans + 1)/2);
        }
    }
}