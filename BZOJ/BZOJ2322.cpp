#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<set>
#define ll long long
using namespace std;
const int N=5010,M=20010,Base=65;
int n,m,Q,tot,Next[M<<1],head[N],tree[M<<1],base,q[M];
ll val[M<<1],f[N],ans[M],b[Base];
bool vis[N],del[M];
struct node{int u,v;ll x;}E[M];
set<ll>S;
void add(int x,int y,ll z)
{
    tot++;
    Next[tot]=head[x];
    head[x]=tot;
    tree[tot]=y;
    val[tot]=z;
}
ll calc(ll x)
{
    for (int i=62;i>=0;i--)
        if (x&(1LL<<i)) x^=b[i];
    return x;
}
void update(ll x)
{
    int flag=-1;
    for (int i=62;i>=0;i--)
    if (x&(1LL<<i))
    {
        if (!b[i]) { b[i]=x;base++;flag=i;break;}
            else x^=b[i];
    }
    ll t;
    if (flag!=-1)
    {
        for (set<ll>::iterator it=S.begin();it!=S.end();it=S.upper_bound(t))
        {
            t=*it;
	    ll tmp=calc(t);
            if (tmp<t) { S.erase(it);S.insert(tmp);}
        }
    }

}
void dfs(int u,int fa)
{
    vis[u]=1;
    ll t=calc(f[u]);
    if (S.find(t)==S.end()) S.insert(t);
    for (int i=head[u];i;i=Next[i])
    {
        int v=tree[i];
        if (v==fa) continue;
        if (vis[v]) update(f[v]^f[u]^val[i]);
        else
        {
            f[v]=f[u]^val[i];
            dfs(v,u);
        }
    }
}
void Insert(int u,int v,ll val)
{
    add(u,v,val);add(v,u,val);
    if (vis[u]&&vis[v])
    {
        update(val^f[u]^f[v]);
        return;
    }
    if (!vis[u]&&!vis[v]) return;
    if (vis[v]) swap(u,v);
    f[v]=f[u]^val;
    dfs(v,u);
}
int main()
{
    scanf("%d%d%d",&n,&m,&Q);
    int Edge=0;
    for (int i=1;i<=m;i++)
    {
        int x,y;ll z;
        scanf("%d%d%lld",&x,&y,&z);
        E[++Edge]=(node){x,y,z};
    }
    for (int i=1;i<=Q;i++)
    {
        scanf("%d",&q[i]);
        del[q[i]]=1;
    }
    for (int i=1;i<=m;i++)
    if (!del[i])
    {
        add(E[i].u,E[i].v,E[i].x);
        add(E[i].v,E[i].u,E[i].x);
    }
    S.insert(0);
    dfs(1,0);
    ans[Q+1]=(ll)S.size()*(1LL<<base)-1;
    for (int i=Q;i>=1;i--)
    {
        Insert(E[q[i]].u,E[q[i]].v,E[q[i]].x);
        ans[i]=(ll)S.size()*(1LL<<base)-1;
    }
    for (int i=1;i<=Q+1;i++) printf("%lld\n",ans[i]);
    return 0;
}
