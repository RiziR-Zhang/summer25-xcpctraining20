#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define x first
#define y second
#define ll long long
const int N=1e6+100000,mod=998244353,INF=1e9+1,M=(1<<21)+10,g=3;

typedef pair<ll,ll> PII;  

ll qpow(ll a,ll k){
    ll res=1;
    a%=mod;
    while(k){
        if(k&1) res=res*a%mod;
        a=a*a%mod;
        k>>=1;
    }
    return res;
}

ll a[N*2],b[N*2],rev[N*2],bit=0,len=1;
ll n,m;

void NTT(ll *a,ll opt){
    for(int i=0;i<len;i++)
        if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(ll mid=1;mid<len;mid<<=1){
        ll tmp=qpow(g,(mod-1)/(mid*2));
        if(opt==-1) tmp=qpow(tmp,mod-2);
        for(int i=0;i<len;i+=mid*2){
            ll w=1;
            for(int j=0;j<mid;j++,w=w*tmp%mod){
                ll x=a[i+j],y=w*a[i+j+mid]%mod;
                a[i+j]=(x+y)%mod,a[i+j+mid]=(x-y+mod)%mod;
            }
        }
    }
}
string s1,s2;
//ll ans[MM];
void solve(){
    cin>>s1>>s2;
		n=s1.length()-1,m=s2.length()-1;
		for(int i=0;i<=n;i++)a[i]=s1[n-i]-'0';
		for(int i=0;i<=m;i++)b[i]=s2[m-i]-'0';
    bit=0,len=1;
    while(len<=n+m) len<<=1,bit++;
    for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1) | ((i&1)<<(bit-1));
    NTT(a,1);NTT(b,1);
    for(int i=0;i<len;i++) a[i]=a[i]*b[i]%mod;
    NTT(a,-1);
    ll inv=qpow(len,mod-2);
    for(int i=0;i<=n+m;i++) a[i]=a[i]*inv%mod;
   // for(int i=0;i<=n+m;i++) cout<<a[i]<<" ";
		//cout<<endl; 
    for(int i=0;i<=4*(n+m);i++){
    	if(a[i]!=0){
    		if(a[i]<0){
    			ll x=llabs(a[i]);
    			if(x%2==0){
    				a[i]=0;
    				a[i+2]+=x/2;
					}
					else{
						a[i]=1;
						a[i+2]+=(x+1)/2;
					}
				}
    		if(a[i]>0){
    			a[i+2]-=a[i]/2;
    			a[i]=a[i]%2;
				}
			}
		}
		bool tag=0;
		for(int i=4*(n+m);i>=0;i--){
			if(tag==0 && a[i]==0)continue;
			if(a[i]!=0){
				tag=1;
			}
			cout<<a[i];
		}
		if(tag==0){
			cout<<"0";
		}
		cout<<'\n';
	for(int i=0;i<=max(len,4*(n+m));i++) a[i]=b[i]=rev[i]=0;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	cin>>T;
	while(T--)solve();
  return 0;
}
