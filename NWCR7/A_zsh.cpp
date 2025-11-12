#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N=110;
int id,m,k,n,p[N][N],a[N],res,ans,c[N];
/*void msort(int b,int e){
    if(b==e)  
		return;
    int mid=(b+e)/2,i=b,j=mid+1,k=b;
    msort(b,mid),msort(mid+1,e);
    while(i<=mid&&j<=e)
    	if(a[i]<=a[j])
    		c[k++]=a[i++];
    	else
    		c[k++]=a[j++],ans+=mid-i+1;
    while(i<=mid)
    	c[k++]=a[i++];
    while(j<=e)
    	c[k++]=a[j++];
    for(int l=b;l<=e;l++)
    	a[l]=c[l];
} */
void solve(){
	cin>>id>>m>>k>>n;
	res=ans=0;
	for(int ii=1;ii<=m;ii++){
		res=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				cin>>p[i][j];
				a[j]=p[i][j];
			}
			for(int k=1;k<=n;k++){
				//cout<<a[k]<<" ";
				ans=0;
				for(int j=k+1;j<=n;j++){
					if(a[k]>a[j])ans=1;
				}
				//cout<<"-"<<ans<<'\n';
				//cout<<a[k]<<" "<<ans<<'\n';
				res+=ans;
			}
			//cout<<'\n';
		}
		//cout<<res<<'\n';
		if(res%2==1)cout<<"1";
		else cout<<"0";
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int T=1;
	//cin>>T;
	while(T--)solve();
  return 0;
}
