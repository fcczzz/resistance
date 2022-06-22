#include<bits/stdc++.h>
#define N 1005
#define M 1000005
#define LL long long
#define db(x) cerr<<#x<<"="<<x<<endl;
#define db2(x,y) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<endl;
#define db3(x,y,z) cerr<<#x<<"="<<x<<" "<<#y<<"="<<y<<" "<<#z<<"="<<z<<endl;
using namespace std;
int rd(){
    int res=0,c,f=0;
    while(!isdigit(c=getchar()))f=c=='-';
    do res=(res<<1)+(res<<3)+(c^48);
    while(isdigit(c=getchar()));
    return f?-res:res;
}
int n,m,S,T;
double a[N][N];
void Print(int n){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n+1;j++)
            printf("%lf ",a[i][j]);
        puts("");
    }
}
double Gauss(int n){
    for(int i=1;i<=n;i++){
        int x=i;
        for(int j=i+1;j<=n;j++)if(abs(a[j][i])>abs(a[x][i]))x=j;
        if(abs(a[x][i])<1e-6)continue;
        if(x!=i)for(int j=1;j<=n+1;j++)swap(a[x][j],a[i][j]);
        for(int j=n+1;j>=i;j--)a[i][j]/=a[i][i];
        for(int j=1;j<=n;j++)if(i!=j)for(int k=n+1;k>=i;k--)a[j][k]-=a[i][k]*a[j][i];
    }
    return a[n][n+1];
}
int s[M],t[M];
double r[M];
vector<int>g[N];
int main(){
    //1~n V_i
    //n+1~n+m I_i
    n=rd(),m=rd();
    for(int i=1;i<=m;i++){
        g[s[i]=rd()].push_back(i);
        g[t[i]=rd()].push_back(i);
        scanf("%lf",&r[i]);
    }
    g[s[m+1]=rd()].push_back(m+1);
    g[t[m+1]=rd()].push_back(m+1);

    //U_1=0
    a[1][1]=1;

    for(int i=2;i<=n;i++){
        //sigma I_j = 0
        for(auto j:g[i])a[i][n+j]=i==s[j]?1:-1;
    }
    //int tot=n;
    for(int i=1;i<=m;i++){
        //U_x - U_y -  I_i * R = 0 
        a[n+i][s[i]]=1;
        a[n+i][t[i]]=-1;
        a[n+i][i+n]=-r[i];
    }
    //U_S - U_T + 1 =0
    a[n+m+1][s[m+1]]=1;
    a[n+m+1][t[m+1]]=-1;
    a[n+m+1][n+m+2]=-1;
    printf("%.6lf\n",1/Gauss(n+m+1));
    return 0;
}
