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
constexpr int LEN = 10;
bool a[LEN + 1];
int simul(bool* A){
    vector<int> v(LEN);
    int fg = 0;
    Rpl(i, 0, LEN){
        v[i] = A[i];
        if(fg == 0 && v[i] == 1) fg = 1;
        if(fg == 1 && v[i] == 0) fg = 2;
    }
    int t = 0;
    while(fg == 2){
        t++;
        Rpl(i, 1, LEN){
            if(v[i - 1] == 1 && v[i] == 0){
                swap(v[i - 1], v[i]);
                i++;
            }
        }
        fg = 0;
        Rpl(i, 0, LEN){
        if(fg == 0 && v[i] == 1) fg = 1;
        if(fg == 1 && v[i] == 0) fg = 2;            
        }
    }
    return t;
}
int calc(bool* A){
    int L = 0, R = LEN - 1;
    while(L < LEN && A[L] == 0) L++;
    while(R >= 0 && A[R] == 1) R--;
    if(L > R) return 0;
    int c = 0;
    while(L < LEN && A[L] == 1) L++, c++;
    while(R >= 0 && A[R] == 0) R--, c++;
    c--;
    int d = 0, ers = 0;
    Rep(i, L, R){
        if(d < 0 && A[i]) ers++;
        if(A[i]) d++;
        else d--;
        if(d > 0){
            c += d;
            d = 0;
        }
        // if((d > 0 && !A[i]) || (d < 0 && A[i])) ers++;
        // if(A[i]) d++;
        // else d--;
    }
    return c + ers + (-d);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int S = 1 << LEN;
    Rpl(t, 1, S){
        Rpl(i, 0, LEN){
            a[i] = (t & (1 << i));
        }
        int Sa = simul(a), Ca = calc(a);
        if(Sa != Ca){
            cout<<t<<' '<<Sa<<' '<<Ca<<endl;
            calc(a);
        }
//        assert(simul(a) == calc(a));
    }
    return 0;
}
