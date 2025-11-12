#include<bits/stdc++.h>
#define Rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define Rpl(i, a, b) for(int i = (a); i < (b); ++i)
using namespace std;
const int mdN = 1e9;
int main()
{
    ios::sync_with_stdio(0);
    freopen("H.in","w",stdout);
    int tsk = 1;
//    cout << tsk << endl;
    mt19937 rnd(998244353);
    while(tsk--){
//        int n = 1000000, q = 1000000;
        int n = 20, q = 10000;
        cout<<n<<' '<<q<<endl;
        Rep(i, 1, n/10){
            int r = rnd() % 1024;
            Rpl(j, 0, 10){
                cout<<((r & (1 << j)) != 0);
            }
        }
        cout<<endl;
        Rep(i, 1, q - 2500){
            int l = rnd() % n + 1, r = rnd() % n + 1;
            if(l > r) swap(l, r);
            cout<<1<<' '<<l<<' '<<r<<endl;
        }
        Rep(i, 1, 2500){
            int l = rnd() % n + 1;
            cout<<2<<' '<<l<<' '<<rnd() % (n - l + 1) + 1<<' '<<rnd() % (n - l + 1) + 1<<endl;
        }
/*        int n = rnd() % 9 + 2;
        cout<<n<<endl;
        Rep(i, 1, n){
            cout<<rnd() % 10 + 1<<' ';
        }
        cout<<endl;*/
    }
    fclose(stdout); 
    return 0;
}
/*int main()
{
    ios::sync_with_stdio(0);
    freopen("C.in","w",stdout);
    int n = 100, q = 1000;
    srand(20250715);
    cout<<n<<' '<<q<<endl;
    Rep(i, 1, n){
        cout<<rand() % mdN + 1<<' ';
    }
    cout<<endl;
    Rpl(i, 1, n){
        cout<<-rand() % 2000000 + 1000000<<' ';
    }
    cout<<endl;
    Rep(i, 1, q){
        cout<<rand()<<endl;
    }
    fclose(stdout);
    return 0;
}*/
/*const int mdN = 1e9;
int main()
{
    ios::sync_with_stdio(0);
    freopen("L.in","w",stdout);
    int tsk = 3;
    cout << tsk << endl;
    srand(998244353);
    for(int t = 1; t <= tsk; t++){
        int n = (tsk == 3 ? 1e5 : 2e5), q = n;
        cout<<n<<' '<<q<<endl;
        Rep(i, 1, n){
            cout<<rand() % mdN<<' ';
        }
        cout<<endl;
        Rep(i, 1, q){
            cout<<rand() % n + 1<<' '<<rand() % mdN + 1<<endl;
        }
    }
    fclose(stdout);
    return 0;
}*/