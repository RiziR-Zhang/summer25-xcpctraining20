#include<iostream>
#include<cstring>
#include<cstdio>

using ll = long long;
const int N = 4e5 + 5;

int a[N];
int w[N],w4[N],w5[N];
int tl[N],tr[N];
int n,Q;


inline int lowbit(int n){return n & (-n);}
ll fl[N],fr[N],f4[N],f5[N];
void add(ll *f,int i,int x){
    if(i < 1)i = 1;
    while(i <= n){
        f[i] += x;
        i += lowbit(i);
    }
}
ll sum(ll *f,int i){
    ll res = 0;
    while(i > 0){ 
        res += f[i];
        i -= lowbit(i);
    }
    return res;
}

void up4(int p){
    if(p < 1 || p + 3 > n)return;
    int x = 0;
    if(a[p] == 2 && a[p + 1] == 0 && a[p + 2] == 2 && a[p + 3] == 0)x = 1;
    if(a[p] == 1 && a[p + 1] == 2 && a[p + 2] == 1 && a[p + 3] == 0)x = 1;
    if(w4[p] != x){
        add(f4,p,x-w4[p]);
        w4[p] = x;
    }
}
void up5(int p){
    if(p < 1 || p + 4 > n)return;
    int x = 0;
    if(a[p] == 2 && a[p + 1] == 1 && a[p + 2] == 2 && a[p + 3] == 0 && a[p + 4] == 0)x = 1;
    if(w5[p] != x){
        add(f5,p,x-w5[p]);
        w5[p] = x;
    }
}

struct node{
    int p,x;
    node operator+ (const node v)const{
        if(x < v.x)
            return v;
        else
            return *this; 
    }
};
node st[N * 4];
void pushup(int p){
    st[p] = st[p<<1] + st[p<<1|1];
}
void build(int p,int l,int r){
    if(l == r){
        st[p] = {l,0};
        return;
    }
    int mid = l + r >> 1;
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    st[p] = {l,0};
}
void change(int p,int l,int r,int x){
    if(l == r){
        st[p] = {l,w[l]};
        return;
    }
    int mid = l + r >> 1;
    if(x <= mid)
        change(p<<1,l,mid,x);
    else
        change(p<<1|1,mid+1,r,x);
    pushup(p);
}
node query(int p,int l,int r,int L,int R){
    if(L <= l && r <= R){
        return st[p];
    }
    if(l == r)return {0,0};
    int mid = l + r >> 1;
    node ans = {0,0};
    if(L <= mid)
        ans = ans + query(p<<1,l,mid,L,R);
    if(R > mid)
        ans = ans + query(p<<1|1,mid + 1,r,L,R);
    return ans;
}

void check(int p){
    if(p < 1 || p + 6 > n)return;
    int x = 0;
    if(a[p] >= 3 && a[p + 1] == 2 && a[p + 2] == 1){
        int t = p + a[p];
        if(t <= n && sum(fr,p+2) == t && sum(fr,t) - t >= 4)
            x = a[p] + 4;
    }
    if(w[p] != x){
        w[p] = x;
        change(1,1,n,p);
    }
}

void init(){
    memset(w,0,sizeof(int) * (n + 1));
    memset(w4,0,sizeof(int) * (n + 1));
    memset(w5,0,sizeof(int) * (n + 1));

    memset(fl,0,sizeof(ll) * (n + 1));
    memset(fr,0,sizeof(ll) * (n + 1));
    memset(f4,0,sizeof(ll) * (n + 1));
    memset(f5,0,sizeof(ll) * (n + 1));
    build(1,1,n);
}
//#define FILE
#define DEBUG
int main(){
freopen("1007.in","r",stdin);
#ifdef FILE
freopen("1007.out","w",stdout);
#endif
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int Tsk;
    std::cin >> Tsk;
    for(int i = 1; i <= Tsk; ++i){
#ifdef DEBUG
std::cout<<"tsk"<<i<<std::endl;
#endif
        std::cin >> n >> Q;
        init();
        for(int i = 1;i <= n;++i){
            std::cin >> a[i];
        }

        tl[1] = 0,tr[n] = n + 1;
        for(int i = 1;i <= n;++i){
            if(a[i])
                tl[i + 1] = i;
            else
                tl[i + 1] = tl[i];
        }
        for(int i = n;i >= 1;--i){
            if(a[i])
                tr[i - 1] = i;
            else
                tr[i - 1] = tr[i];
        }
        tr[0] = 0;
        //printf("-------------");
        for(int i = 1;i <= n;++i){
            if(tr[i] != tr[i - 1])
                add(fr,i,tr[i] - tr[i-1]);
            if(tl[i] != tl[i - 1])
                add(fl,i,tl[i] - tl[i-1]);
        }
        /*printf("fr:");
        for(int i = 1;i <= n;++i)
            printf("%lld ",sum(fr,i));
        putchar('\n');*/
        for(int i = 1;i <= n;++i){
            if(a[i]){
                up4(i);
                up5(i);
                check(i);
            }
        }

        while(Q--){
            int op;
            std::cin >> op;
            if(op == 1){
                int p,x;
                std::cin >> p >> x;
                if(a[p] == x)continue;
                if(!a[p]){
                    int l = sum(fl,p);
                    int r = sum(fr,p);
                    add(fl,p+1,p-l);
                    add(fl,r+1,l-p);
                    add(fr,l-1,p-r);
                    add(fr,p-1,r-p);
                }
                if(a[p] && !x){
                    int l = sum(fl,p);
                    int r = sum(fr,p);
                    add(fl,p+1,l-p);
                    add(fl,r+1,p-l);
                    add(fr,l-1,r-p);
                    add(fr,p-1,p-r);
                }
                a[p] = x;
                up4(p);
                up5(p);
                check(p);
                int u = sum(fl,p);
                for(int i = 1;i <= 4;++i){
                    if(u < 1)break;
                    //printf("u:%d\n",u);
                    up4(u);
                    up5(u);
                    check(u);
                    u = sum(fl,u);
                }
            }
            else{
                int L,R;
                std::cin >> L >> R;
                int ans = 0;;
                node u = query(1,1,n,L,R);
                if(u.p + u.x - 1 > R){
                    if(u.p > L)
                        u = query(1,1,n,L,u.p-1);
                    else
                        u.x = 0;
                }
                ans = std::max(ans,u.x);
                if(R - L >= 3 && sum(f4,R - 3) - sum(f4,L-1))
                    ans = std::max(ans,4);
                if(R - L >= 4 && sum(f5,R - 4) - sum(f5,L-1))
                    ans = std::max(ans,5);
                std::cout<<ans<<'\n';
            }
        }
    }
fclose(stdin);
#ifdef FILE
fclose(stdout);
#endif
}