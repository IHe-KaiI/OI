#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=1000100,M=2000100;
int n,tot,a[N],Next[M],head[N],tree[M],X,Y,E,cnt,visit[N];
long long f[N][2];
void add(int x,int y)
{
    tot++;
    Next[tot]=head[x];
    head[x]=tot;
    tree[tot]=y;
}
void dfs(int u,int fa)
{
    visit[u]=cnt;
    for (int i=head[u];i;i=Next[i])
    {
        int v=tree[i];
        if ((i^1)==fa) continue;
        if (visit[v]!=cnt) dfs(v,i);
        else
        {
            X=u;Y=v;E=i;
            continue;
        }
    }
}
void dp(int u,int fa)
{
    visit[u]=cnt;
    f[u][0]=0;f[u][1]=a[u];
    for (int i=head[u];i;i=Next[i])
    {
        int v=tree[i];
        if ((i^1)!=fa&&i!=E&&(i^1)!=E)
        {
            dp(v,i);
            f[u][0]+=max(f[v][0],f[v][1]);
            f[u][1]+=f[v][0];
        }
    }
}
int main()
{
    scanf("%d",&n);
    tot=1;
    for (int i=1;i<=n;i++)
    {
        int x;
        scanf("%d%d",&a[i],&x);
        add(i,x);add(x,i);
    }
    cnt=0;
    long long ans=0;
    for (int i=1;i<=n;i++)
    if (!visit[i])
    {
        cnt++;
        dfs(i,-1);
        cnt++;
        dp(X,-1);
        long long Ans=f[X][0];
        cnt++;
        dp(Y,-1);
        ans+=max(Ans,f[Y][0]);
    }
    printf("%lld\n",ans);
    return 0;
}
