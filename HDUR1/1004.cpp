#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
//#define MINI
//#define FILE
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
#ifndef MINI
constexpr int mN = 55, mS = 1100055, mL = mS << 1, mV = 128;
#else
constexpr int mN = 5, mS = 129, mL = mS << 1, mV = 128;
#endif
int n, Len, idlen[mS], b[mS], maxsum;
char str[mS];

int sa[mL],rk[mL],id[mL],odrk[mL],cnt[mL];
bool cmprk(int x,int y,int j){return (odrk[x]==odrk[y] && odrk[x+j]==odrk[y+j]);}
void GetSA(char *s,int l){
    int m = mV, p = 0;
	for(int i = 0;i <= m;i++) cnt[i] = 0;
	for(int i = 1;i <= l;i++) cnt[rk[i] = s[i]]++;
	for(int i = 1;i <= m;i++) cnt[i] += cnt[i - 1];
	for(int i = l;i >= 1;i--) sa[cnt[rk[i]]--] = i;
	for(int w = 1;w <= l;w <<= 1){
		int p = 0;
		for(int i = l;i > l - w;i--) id[++p] = i;
		for(int i = 1;i <= l;i++){
			if(sa[i] > w) id[++p] = sa[i] - w;
			odrk[i] = rk[i];
		}
		for(int i = 0;i <= m;i++) cnt[i] = 0;
		for(int i = 1;i <= l;i++) cnt[rk[id[i]]]++;
		for(int i = 1;i <= m;i++) cnt[i] += cnt[i - 1];
		for(int i = l;i >= 1;i--) sa[cnt[rk[id[i]]]--] = id[i];
		rk[sa[1]] = m = 1;
		for(int i = 2;i <= l;i++){
			rk[sa[i]] = (odrk[sa[i]] == odrk[sa[i - 1]] && 
			odrk[sa[i] + w] == odrk[sa[i - 1] + w] ? m : ++m);
		}
		if(m == l) break;
	}

/*    memset(cnt, 0, sizeof(int) * m);
    Rep(i, 1, l) cnt[rk[i] = s[i]]++;
    Rep(i, 1, m) cnt[i] += cnt[i - 1];
    for(int i = l; i >= 1; --i) sa[cnt[rk[i]]--] = i;


    for(int w = 1;; w <<= 1, m = p){
        int cur = 0;
        for(int i = l - w + 1; i <= l; ++i) id[++cur] = i;
        for(int i = 1; i <= l; ++i)
            if(sa[i] > w) id[++cur] = sa[i] - w;

        memset(cnt, 0, sizeof(int) * max(m, l));
        Rep(i, 1, l) cnt[rk[i]]++;
        Rep(i, 1, m) cnt[i] += cnt[i - 1];
        for(int i = l; i >= 1; --i) sa[cnt[rk[id[i]]]--] = id[i];

        p = 0;
        memcpy(odrk, rk, sizeof(int) * max(m, l));
        Rep(i, 1, l){
            if(cmprk(sa[i], sa[i - 1], w)) rk[sa[i]] = p;
            else rk[sa[i]] = ++p;
        }
        if(p == l) break;
    }*/
/*
#define f(i,a,b) for(int i=a;i<b;i++)
#define g(i,b,a) for(int i=b-1;i>=a;i--)
    f(i,0,l)cnt[rk[i]=s[i]]++;	f(i,1,mV)cnt[i]+=cnt[i-1];	g(i,l,0)sa[--cnt[rk[i]]]=i;
	for(int b=1,p=0,v=mV;b<=l&&p<=l;b<<=1,v=(++p)){p=0;memset(cnt,0,sizeof(cnt));memcpy(odrk,rk,sizeof(odrk));
		f(i,l-b,l)id[p++]=i;	f(i,0,l)if(sa[i]>=b)id[p++]=sa[i]-b;
		f(i,0,l)cnt[RkId[i]=rk[id[i]]]++;	f(i,1,v)cnt[i]+=cnt[i-1];	g(i,l,0)sa[--cnt[RkId[i]]]=id[i];
		rk[sa[p=0]]=0;	f(i,1,l)rk[sa[i]]=(cmprk(sa[i],sa[i-1],b)?p:(++p)); if(p+1==l)break;}
#undef f
#undef g*/
}
int height[mL];
void getHeight(char *s, int len){
    int k = 0;
    Rep(i, 1, len){
        if(k) --k;
        if(rk[i] == 1) k = 0;
        else{
            while(s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        }
        height[rk[i]] = k;
    }
    return;
}
struct Node{
    int fa, sz, Lm[mN];
    void init(int id, int bel, int L){
        fa = id;
        sz = 1;
        memset(Lm + 1, 0, sizeof(int) * n);
        Lm[bel] = L;
    }
    int operator += (const Node &nd){
        sz += nd.sz;
        int sum = 0, num = 0;
        Rep(i, 1, n){
            Lm[i] = max(Lm[i], nd.Lm[i]);
            sum += Lm[i];
            num += (Lm[i] != 0);
        }
        if(num <= 1) sum = 0;
        return sum;
    }
};
//struct SPDSU{
    Node nd[mL];
    int ffa(int x){
        if(x == nd[x].fa) return x;
        return nd[x].fa = ffa(nd[x].fa);
        //return x == nd[x].fa ? x : nd[x].fa = ffa(nd[x].fa);
    }
    inline void merge(int x, int y){
        x = ffa(x), y = ffa(y);
        if(x == y) return;
        if(nd[x].sz < nd[y].sz) swap(x, y);
        int cnt = 0;
        nd[y].fa = x;
        int sum = (nd[x] += nd[y]);
        if(sum > 0){
            maxsum = max(maxsum, sum);
        }
    }
//}spDSU;
vector<int> list[mL];
void solve(){
    int maxlcp = 0;
    Rep(i, 1, Len){
        maxlcp = max(maxlcp, height[i]);
        list[height[i]].push_back(i);
        nd[i].init(i, b[sa[i]], idlen[sa[i]]);
    }

    LL ans = 0;
    maxsum = 0;
    for(int i = maxlcp; i >= 0; --i){
        for(auto j: list[i]){
            merge(j - 1, j);//& upd
        }
        ans = max(ans, 1ll * i * maxsum);
        list[i].clear();
    }

    cout<<ans<<endl;
}
void ALLClear(){
    Len++;
    memset(sa, 0, sizeof(char) * Len);
    memset(rk, 0, sizeof(char) * Len);
    memset(id, 0, sizeof(char) * Len);
}
int main()
{
#ifdef FILE
    freopen("1004.in", "r", stdin);
    freopen("1004.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n;
        Len = 0;
        Rep(i, 1, n){
            str[++Len] = 32 + i;
            b[Len] = 0;
            cin>>(str + Len + 1);
            int sublen = strlen(str + Len + 1);
            Rep(j, 0, sublen) b[Len + j] = i, idlen[Len + j] = j;
            Len += sublen;
        }
        GetSA(str, Len);
        getHeight(str, Len);

        solve();
        //ALLClear();
    }
#ifdef FILE
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
