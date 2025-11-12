#include<iostream>
#include<cstdio>

using ll = long long;
const ll P = 1e9 + 7;
const int N = 3e5 + 5;
struct node{
    ll A,_A,B,_B,C,D,_D,E,_E;
    void print(){
        printf("[ %lld + %lld << %lld << %lld + %lld ]\n",A,B,C,_D,_E);
    }
};
node w[N];
char typ[N];
int ls[N],rs[N];

ll qpow(ll a,ll b,ll p){
    ll res = 1;
    a %= p;
    while(b > 0){
        if(b & 1)res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

ll sum(node a){
    if(a.E == -1){
        return a.A % P;
    }
    else if(a.C == -1){
        return (a.A + a.B +a.E) % P;
    }
    else
        return (a.A + a.B) * qpow(2,a.C + a._D + a._E,P) % P;
}

void dfs(int i){
    if(w[i].A != -1)return;
    //printf("u : %d\n",i);
    int u = ls[i];
    int v = rs[i];
    dfs(u),dfs(v);
    w[i] = w[u];
    if(typ[i] == '<'){
        if(w[i].C == -1){
            if(w[i].E != -1){
                w[i].B = (w[i].B + w[i].E) % P;
                w[i]._B = (w[i]._B + w[i]._E) % (P - 1);
            }
            w[i].C = 0;
        }
        else{
            w[i].C = (w[i].C + w[i]._D + w[i]._E) % (P - 1);
        }
        
        if(w[v].C == -1){
            if(w[v].E == -1){
                w[i].E = w[v].A;
                w[i]._E = w[v]._A;
                w[i].D = w[i]._D = 0;
            }
            else{
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
                w[i].D = (w[v].A + w[v].B) % P;
                w[i]._D = (w[v]._A + w[v]._B) % (P - 1);
            }
        }
        else{
            w[i].C = (w[i].C + w[v]._A + w[v]._B + w[v].C) % (P - 1);
            w[i].D = w[v].D;
            w[i].E = w[v].E;
            w[i]._D = w[v]._D;
            w[i]._E = w[v]._E;
        }
    }
    else if(typ[i] == '+'){
        if(w[v].E == -1){
            if(w[i].E == -1){
                w[i].E = w[v].A;
                w[i]._E = w[v]._A;
            }
            else if(w[i].C == -1){
                w[i].B = (w[i].B + w[i].E) % P;
                w[i]._B = (w[i]._B + w[i]._E) % (P - 1);
                w[i].E = w[v].A;
                w[i]._E = w[v]._A;
            }
            else{
                w[i].D = (w[i].D + w[i].E) % P;
                w[i]._D = (w[i]._D + w[i]._E) % (P - 1);
                w[i].E = w[v].A;
                w[i]._E = w[v]._A;
            }
        }
        else if(w[v].C == -1){
            if(w[i].C == -1){
                if(w[i].E != -1){
                    w[i].B = (w[i].B + w[i].E) % P;
                    w[i]._B = (w[i]._B + w[i]._E) % (P - 1);
                }
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
                w[i].B = (w[i].B + w[v].A + w[v].B) % P;
                w[i]._B = (w[i]._B + w[v]._A + w[v]._B) % (P - 1);
            }
            else{
                w[i].D = (w[i].D + w[i].E + w[v].A + w[v].B) % P;
                w[i]._D = (w[i]._D + w[i]._E + w[v]._A + w[v]._B) % (P - 1);
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
            }
        }
        else{
            if(w[i].C == -1){
                if(w[i].E == -1)w[i].E = w[i]._E = 0;
                w[i].B = (w[i].B + w[i].E + w[v].A + w[v].B) % P;
                w[i]._B = (w[i]._B + w[i]._E + w[v]._A + w[v]._B) % (P - 1);
                w[i].C = w[v].C;
                w[i].D = w[v].D;
                w[i]._D = w[v]._D;
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
            }
            else{
                w[i].C = (w[i].C + w[v].C + w[i]._D + w[i]._E + w[v]._A + w[v]._B) %(P - 1);
                w[i].D = w[v].D;
                w[i]._D = w[v]._D;
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
            }
        }
    }
    else if(typ[i] == '*'){
        if(w[v].E == -1){
            if(w[i].E == -1){
                w[i].A = w[i].A * w[v].A % P;
                w[i]._A = w[i]._A * w[v]._A % (P - 1);               
            }
            else{
                w[i].E = w[i].E * w[v].A % P;
                w[i]._E = w[i]._E * w[v]._A % (P-1);
            }
        }
        else if(w[v].C == -1){
            if(w[i].E == -1){
                w[i].A = w[i].A * w[v].A % P;
                w[i]._A = w[i]._A * w[v]._A % (P - 1);
                w[i].B = w[v].B;
                w[i]._B = w[v]._B;
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
            }
            else if(w[i].C == -1){
                w[i].B = (w[i].B + w[i].E * w[v].A + w[v].B) % P;
                w[i]._B = (w[i]._B + w[i]._E * w[v]._A + w[v]._B) % (P - 1);
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
            }
            else{
                w[i].D = (w[i].D + w[i].E * w[v].A + w[v].B) % P;
                w[i]._D = (w[i]._D + w[i]._E * w[v]._A + w[v]._B) % (P - 1);
                w[i].E = w[v].E;
                w[i]._E = w[v]._E;
            }
        }
        else{
            if(w[i].E == -1){
                ll x = w[i].A * w[v].A % P;
                ll _x = w[i]._A * w[v]._A % (P - 1);
                w[i] = w[v];
                w[i].A = x;
                w[i]._A = _x;
            }
            else if(w[i].C == -1){
                w[i].B = (w[i].B + w[i].E * w[v].A + w[v].B) % P;
                w[i]._B = (w[i]._B + w[i]._E * w[v]._A + w[v]._B) % (P - 1);
                w[i].C = w[v].C;
                w[i].D = w[v].D;
                w[i].E = w[v].E;
                w[i]._D = w[v]._D;
                w[i]._E = w[v]._E;
            }
            else{
                w[i].C = (w[i].C + w[v].C + w[i]._D + w[i]._E * w[v]._A + w[v]._B) % (P - 1);
                w[i].D = w[v].D;
                w[i].E = w[v].E;
                w[i]._D = w[v]._D;
                w[i]._E = w[v]._E;
            }
        }
    }
}

int main(){
    int n; 
    scanf("%d",&n);
    for(int i = 1;i <= n;++i){
        w[i] = {-1,-1,0,0,-1,0,0,-1,-1};
        getchar();
        char op;
        scanf("%c",&op);
        typ[i] = op;
        if(op == 'N'){
            ll x;
            scanf("%lld",&x);
            w[i].A = w[i]._A = x;
        }
        else
            scanf("%d%d",ls + i,rs + i);
    }
    for(int i = 1;i <= n;++i){
        dfs(i);
        //w[i].print();
        printf("%lld\n",sum(w[i]));
    }
}