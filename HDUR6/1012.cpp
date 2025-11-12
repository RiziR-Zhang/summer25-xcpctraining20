#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<cassert>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
//constexpr int mN = ;


#define swap(x,y) x^=y^=x^=y
typedef vector<long long> vll;
constexpr int mS=250005;
constexpr int mN = 200005, stdN = 200000;
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
			swap(A[i],A[r[i]]);
	
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
	for(int i=0;i<limit;++i)
		p[i]=(a[i]*b[i])%mdN;
	NTT(p,limit,-1);
	LL inv=qp(limit,mdN-2);
	for(int i=0;i<limit;++i)//lenp?
		p[i]=p[i]*inv%mdN;
	return p;
}

LL fac[mN], ifac[mN], inv[mN];
void mathinit(int LEN = stdN){
    fac[0] = ifac[0] = 1;
    Rep(i, 1, LEN) fac[i] = fac[i - 1] * i % mdN;
    ifac[LEN] = qp(fac[LEN], mdN - 2);
    for(int i = LEN; i; --i){
        inv[i] = ifac[i] * fac[i - 1] % mdN;
        ifac[i - 1] = ifac[i] * i % mdN;
    }
}

int n, cnt;
LL a[mN];
bool uz[mN];
void calcNormal(){
    auto E = [=](LL v){return (v + inv[v]) % mdN * inv[4] % mdN;};
    LL ans = 2;
    for(int i = n; i > 1; --i){
        ans = (ans * E(a[i]) + 1) % mdN;
    }
    ans = ans * a[1] % mdN * inv[2] % mdN;
    cout<<ans<<endl;
}
void solve(){
    Rep(i, 1, n){

    }
}
void ALLClear(){
    
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    mathinit();
    while(tsk--){
        cin>>n;
        memset(uz + 1, 0, sizeof(int) * n);
        cnt = 0;
        Rep(i, 1, n){
            cin>>a[i];
            if(a[i] != -1)
                uz[a[i]] = 1;
            else
                cnt++;
        }
        if(cnt == 1){
            int v = 0;
            Rep(i, 1, n){
                if(!uz[i]){
                    v = i;
                    break;
                }
            }
            Rep(i, 1, n){
                if(a[i] == -1){
                    a[i] = v;
                    break;
                }
            }
            cnt = 0;
        }
        if(cnt == 0){
            calcNormal();
            continue;
        }
        
        solve();
        ALLClear();
    }
    return 0;
}
