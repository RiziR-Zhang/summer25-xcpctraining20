#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<random>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 1000005, mV = 5000005, stdV = 5000000;
int n, minfac[mV], a[mN], pr[mV], prn, squflag, hsh[mV];
bool odd[mV];
mt19937 rng(20250722);
void sieve(){
    Rep(i, 2, stdV){
        if(minfac[i] == 0){
            minfac[i] = i;
            hsh[i] = rng() % 1000000009 + 1;
            pr[++prn] = i;
        }
        for(int j = 1; j <= prn && pr[j] * i <= stdV; ++j){
            minfac[pr[j] * i] = pr[j];
            hsh[pr[j] * i] = hsh[i] ^ hsh[pr[j]];
            if(i % pr[j] == 0) break;
        }
    }
}
void process(int x){
    int cnt, fac;
    while(x > 1){
        fac = minfac[x];
        cnt = 0;
        while(x % fac == 0){
            cnt++;
            x /= fac;
        }
        if(cnt & 1){
            if(odd[fac]) squflag--;
            else squflag++;
            odd[fac] ^= 1;
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    sieve();
    while(tsk--){
        cin>>n;
        squflag = 0;
        bool flag = (n % 2 == 1);
        int shash = 0;
        Rep(i, 1, n){
            cin>>a[i];
            if(!flag)
                shash ^= hsh[a[i]];
//            process(a[i]);
        }
        if(flag || shash == 0){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
/*            Rep(i, 1, n){
                for(int A = a[i]; A > 1; A /= minfac[A]){
                    odd[minfac[A]] = 0;
                }
            }*/
        }
    }
    return 0;
}
