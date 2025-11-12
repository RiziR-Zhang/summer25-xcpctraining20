#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
#include<cmath>
using namespace std;

// #define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mP = 200005, mN = 200005, mSZ = 500005;

#define mswap(x,y) x^=y^=x^=y
typedef vector<long long> vll;
constexpr int mS=600005;
constexpr LL mdN=998244353,g=3,gi=332748118;
int r[mS<<1];
inline LL qp(LL a,LL b){
	LL pw=1;
	while(b){
		if(b&1) pw=pw*a%mdN;
		a=a*a%mdN;
		b>>=1;
	}
	return pw;
}
void build_bitrev(int lg){
	int pw=1<<lg;
	for(int i=0;i<pw;++i)
		r[i]=(r[i>>1]>>1)|((i&1)<<(lg-1));
}
inline void NTT(vll& A,int limit=0,int type=1){//note & 
	for(int i=0;i<limit;++i)
		if(i<r[i])
			mswap(A[i],A[r[i]]);
	
	for(int mid=1;mid<limit;mid<<=1){
		LL wn1=qp(type==1?g:gi,(mdN-1)/(mid<<1));
		for(int j=0;j<limit;j+=(mid<<1)){
			LL w=1;
			for(int k=0;k<mid;++k,w=w*wn1%mdN){
				LL x=A[j+k],y=w*A[j+k+mid]%mdN;//int ok
				A[j+k]=(x+y)%mdN;
				A[j+k+mid]=(x-y+mdN)%mdN;
			}
		}
	}
}
vll polymul(vll a,vll b){
	int lena=a.size(),lenb=b.size(),lenp=lena+lenb-1;
	int limit=1,lg=0;
	while(limit<lenp) limit<<=1,++lg;
	a.resize(limit),b.resize(limit);
	build_bitrev(lg);
	NTT(a,limit,1);
	NTT(b,limit,1);
	vll p(limit);//?
//	assert(int(p.size())>=limit);
	for(int i=0;i<limit;++i)
		p[i]=(a[i]*b[i])%mdN;
	NTT(p,limit,-1);
	LL inv=qp(limit,mdN-2);
	for(int i=0;i<limit;++i)//lenp?
		p[i]=p[i]*inv%mdN;
	return p;
}
int n, m;
vll day[mN];
void solve()
{
    cin>>n>>m;
    Rep(i, 1, n){
        day[i].resize(m * 2 + 1);
        Rpl(j, 0, m * 2 + 1){
            cin>>day[i][j];
        }
    }
    int B = max(1, (int)sqrt(n)), pointO = 0;
    vll ans(B * m + 1, 0);
    ans[0] = 1;
    LL P = 0;
    for(int d = 1; d <= n; d += B){
        int targ = min(n, d + B - 1);
        vll cur(B * m + 1, 0);
        Rep(i, 0, B * m){
            cur[i] = ans[i];
            ans[i] = 0;
        }
        vll mul(1, 1);
        int pointO = 0;
        for(int inl = d; inl < d + B && inl <= n; ++inl){
            mul = polymul(mul, day[inl]);
            cur = polymul(cur, day[inl]);
#ifdef DEBUG
cout<<"#"<<d<<":"<<inl<<endl;
for(auto mi: mul){
    cout<<mi<<' ';
}
cout<<endl;
for(auto ci: cur){
    cout<<ci<<' ';
}
cout<<endl;
#endif
            Rpl(i, 0, m){
                P = (P + cur[i]) % mdN;
                cur[i] = cur[i + m];
            }
            Rep(i, m, pointO * m){
                cur[i] = cur[i + m];
            }
            pointO += m;
            cur.resize(pointO + 1);
            cout<<(1 - P + mdN) % mdN<<' ';
        }
        ans = polymul(ans, cur);
        Rep(i, 0, pointO){
            ans[i] = (ans[i + pointO] + cur[i]) % mdN;
        }
        Rep(i, pointO + 1, targ * m){
            ans[i] = ans[i + pointO];
        }
        ans.resize(targ * m + 1);
    }
    cout<<endl;
}
//#define FILE
int main()
{
#ifdef FILE
freopen("1004.in","r",stdin);
freopen("1004.out","w",stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        solve();
    }
#ifdef FILE
fclose(stdin);
fclose(stdout);
#endif
    return 0;
}
