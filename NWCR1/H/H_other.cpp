#include <bits/stdc++.h> 
#pragma GCC optimize(3)
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
using namespace std;
int l1[2000005],r1[2000005],num[2000005],flip[2000005],opt,l,r,a,b,n,q;
long long js[2000005]; 
char ch[2000005];
struct bs{
    int sz;
    int num[100005];
};
const int S1=16; 
bs getbs(int l,int r) {
    l--;
    r--;
    bs a;
    a.sz=0;
    int pos=(S1-1)-l%S1;
    int i=l;
    while (i+S1<=r){
        int i1=i/S1;
        a.num[a.sz]=((num[i1]&((1<<pos+1)-1))<<((S1-1)-pos))|((num[i1+1]&((1<<S1)-(1<<pos)))>>(pos+1));
        i+=S1;
        a.sz++;
    }
    int i1=i/S1;
    if (r-i<pos) a.num[a.sz]=((num[i1]&((1<<pos+1)-(1<<((S1-1)-r%S1))))<<((S1-1)-pos)); else
    a.num[a.sz]=((num[i1]&((1<<pos+1)-1))<<((S1-1)-pos))|((num[i1+1]&((1<<S1)-(1<<((S1-1)-r%S1))))>>(pos+1));
//  cout<<a.sz<<" "<<a.num[0]<<" "<<((num[i1]&((1<<pos+1)-1))<<((S1-1)-pos))<<" "<<((num[i1+1]&((1<<S1)-(1<<((S1-1)-r%S1))))>>(pos+1))<<" "<<num[i1+1]<<" "<<((1<<S1)-(1<<((S1-1)-r%S1)))<<endl; 
    return a; 
}
long long C2(int x){
    return (long long)x*(x-1)/2;
}
long long xorbs(bs a,bs b,int len) {
    bs c;
    c.sz=a.sz;
    long long ans=0;
    int k=0;
    int r2=0;
    for (int i=0;i<a.sz;i++){
        c.num[i]=a.num[i]^b.num[i]^((1<<S1)-1); 
        if (l1[c.num[i]]==S1) r2+=S1; else {
            ans=ans+C2(r2+l1[c.num[i]]+1)+js[c.num[i]];
            r2=r1[c.num[i]];
            k=0;
        }
    }
    c.num[a.sz]=a.num[a.sz]^b.num[a.sz]^((1<<S1)-1); 
    for (int i=0;i+S1*a.sz<len;i++) {
        if ((1<<((S1-1)-i))&c.num[a.sz]) r2++; else {ans+=C2(r2+1),r2=0;}
    }
    ans+=C2(r2+1);
    return ans;;
}
signed main(){
freopen("H.in","r",stdin);
freopen("Hfase.out","w",stdout);

        ios::sync_with_stdio(0);
    for (int i=0;i<(1<<S1);i++) {
        for (int j=(S1-1);j>=0;j--)
            if (i&(1<<j)) l1[i]++; else break;
        for (int j=0;j<=(S1-1);j++)
            if (i&(1<<j)) r1[i]++; else break;
        int k=0;
        for (int j=r1[i];j<S1-l1[i];j++) {
            if (i&(1<<j)) k++; else k=0;
            js[i]+=k;
        }
    }
    cin>>n>>q;
    for (int i=1;i<=n;i++)  {
        cin>>ch[i];
        num[(i-1)/S1]|=((ch[i]-48)<<((S1-1)-(i-1)%S1));
    }
    for (int i=1;i<=q;i++) {
        cin>>opt;
        if (opt==1) {
            cin>>l>>r;
            l--;r--;
            if (l/S1==r/S1) 
                num[l/S1]^=((1<<(S1-l%S1))-(1<<((S1-1)-r%S1)));
             else {
                num[l/S1]^=((1<<(S1-l%S1))-1);
                num[r/S1]^=((1<<S1)-(1<<((S1-1)-r%S1)));
                flip[l/S1+1]^=1;
                flip[r/S1]^=1;
            }
        }
        if (opt==2) {
            for (int i=0;i<=(n-1)/S1;i++) {
                if (i) flip[i]^=flip[i-1];
                if (flip[i]) num[i]^=((1<<S1)-1); 
                if (i) flip[i-1]=0;
            }
            flip[(n-1)/S1]=0;
            cin>>l>>a>>b;
            bs a1=getbs(a,a+l-1);
            bs b1=getbs(b,b+l-1);
            long long ans=xorbs(a1,b1,l);
            cout<<ans<<endl;
        }
    }
fclose(stdin);
fclose(stdout);
    return 0;
}