#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#include<fstream>
#include<cassert>
using namespace std;

#define DEBUG
#define Rpl(i,a,b) for(int i = (a); i < (b); ++i)
#define Rep(i,a,b) for(int i = (a); i <= (b); ++i)
typedef long long LL;
typedef pair<int,int> pii;
constexpr int mN = 10005, mK = 67;
int n;
struct Node{
    int a, b, c, ans;
}sam[mN];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ifstream samIN("B.in");
    samIN >> n;
    Rep(i, 1, n){
        samIN>>sam[i].a>>sam[i].b>>sam[i].c;
    }
    samIN.close();
    ifstream samOUT("B.out");
    int ignore = 0;
    int ALLRIGHT = 0;
    Rep(i, 1, n){
        samOUT >> sam[i].ans;
        if(sam[i].ans == -1) ignore++;
        else{
            __int128 x = sam[i].a, y = sam[i].b, z = sam[i].c;
            int op;
            Rep(t, 1, sam[i].ans){
                samOUT >> op;
                if(op == 1){
                    x = x * 2;
                }else if(op == 2){
                    y = y / 2;
                }else if(op == 3){
                    x = x ^ y;
                }else if(op == 4){
                    y = x ^ y;
                }else
                    assert(0);
            }
            if(sam[i].ans > 65 || x != z || y != z){
                ALLRIGHT = i;
            }
        }
    }
    samOUT.close();
    if(ALLRIGHT == 0) cout<<"all right (ignored "<<ignore<<")"<<endl;
    else cout<<"mistake at #"<<ALLRIGHT<<endl;
    return 0;
}
