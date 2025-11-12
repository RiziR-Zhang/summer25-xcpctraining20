#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 200005;
char s[mN];
int o[mN], p[mN];
pii vpair[mN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    cin>>s;
    bool sameChar = 1;
    for(int i = 1; i < n && sameChar; ++i){
        sameChar &= (s[i] == s[i - 1]);
    }
    if(sameChar){
        cout<<-1<<endl;
        return 0;
    }
    o[0] = 0;
    int l = 0, r = 0;
    for(int i = 0; i < n - 1; ++i){
        if(s[i] == '1'){
            o[i + 1] = --l;
        }else{
            o[i + 1] = ++r;
        }
    }
    if(s[n - 1] == '0' && o[n - 1] > 0){
        for(int j = n - 1; s[j] == '0'; --j){
            o[j] -= n;
        }
    }
    if(s[n - 1] == '1' && o[n - 1] < 0){
        for(int j = n - 1; s[j] == '1'; --j){
            o[j] += n;
        }
    }
    Rpl(i, 0, n){
        vpair[i] = {o[i], i};
    }
    sort(vpair, vpair + n);
    Rpl(i, 0, n){
        p[vpair[i].second] = i;
    }
    Rpl(i, 0, n){
        cout<<p[i]<<' ';
    }
    cout<<endl;
    return 0;
}
