#include<iostream>
#include<cmath>
using namespace std;
typedef long long LL;
int main()
{
    ios::sync_with_stdio(false);
    int tsk;
    LL a,b;
    cin>>tsk;
    while(tsk--){
        cin>>a>>b;
        LL dif = llabs(a * a - b * b);
        if(dif == 3) cout<<1<<endl;
        else cout<<(dif - dif / 2 + dif / 4 - 2)<<endl;
    }
    return 0;
}