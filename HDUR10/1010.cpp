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
constexpr int mN = 4000005;
int n, m;
struct Seq{
    int a[mN], sand[mN], x[mN];
    void init(int num, int siz){
        memset(a, 0, sizeof(int) * (num * siz));
    }
    void xtrans(){
        Rep(i, 1, m){
            if(s[i] <= '9'){
                x[i] = s[i] - '0';
            }else{
                x[i] = s[i] - 'a' + 10;
            }
        }
    }
    void trans(int id){
        int st = m * (id - 1);
        Rep(i, 1, m){
            if(s[i] <= '9'){
                a[st + i] = s[i] - '0';
            }else{
                a[st + i] = s[i] - 'a' + 10;
            }
        }
    }
    void reset(){
        memset()
    }
}blk;
char s[mN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tsk;
    cin>>tsk;
    while(tsk--){
        cin>>n>>m;
        cin>>s;
        blk.init(n, m);
        blk.xtrans();
        Rep(i, 1, n){
            cin>>s;
            blk.trans(i);
        }
        blk.reset();
        Rep(i, 1, n){
            blk.orNUM(i);
            if(blk.chk()){
                ans++;
                blk.reset();
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}
