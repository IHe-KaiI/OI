#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=200010;
int n,m,S[N],f[N][20],g[N][20],sum[N],K,Log[N],a[N],b[N];
struct node{int x,l;}Q[N];
bool cmp(node a,node b) { return a.x<b.x;}
void pre()
{
    for (int i=1;i<=K;i++) f[i][0]=a[i]+sum[b[i]],g[i][0]=a[i]-sum[b[i]];
    Log[1]=0;
    for (int i=2;i<=K;i++) Log[i]=Log[i>>1]+1;
    for (int i=1;i<=18;i++)
        for (int j=1;j<=K;j++)
        {
            f[j][i]=min(f[j][i-1],f[j+(1<<(i-1))][i-1]);
            g[j][i]=min(g[j][i-1],g[j+(1<<(i-1))][i-1]);
        }
}
int query(int x,int y,int p)
{
    int z=Log[y-x+1];
    if (!p) return min(g[x][z],g[y-(1<<z)+1][z]);
        else return min(f[x][z],f[y-(1<<z)+1][z]);  
}
int erfenL(int l,int r,int x)
{
    while (l<r)
    {
        int mid=(l+r)>>1;
        int p=max(1,mid+mid-b[x]+1),L=lower_bound(b+1,b+K+1,p)-b,X=upper_bound(b+1,b+K+1,mid)-b-1;
	if (L>=x) { r=mid;continue;}
	if (b[X]<=mid&&L<x&&-query(L,min(X,x-1),0)+(a[x]+sum[b[x]])>=sum[mid]*2) { l=mid+1;continue;}
	if (X+1<=x-1&&query(X+1,x-1,1)-(a[x]-sum[b[x]])<=sum[mid]*2) { l=mid+1;continue;}
	r=mid;
    }
    return r;
}
int erfenR(int l,int r,int x)
{
    while (l<r)
    {
        int mid=(l+r+1)>>1;
        int p=min(n,mid+mid-b[x]-1),R=upper_bound(b+1,b+K+1,p)-b-1,X=lower_bound(b+1,b+K+1,mid)-b;
	if (R<=x) { l=mid;continue;}
        if (b[X]>=mid&&R>x&&query(max(x+1,X),R,1)-(a[x]-sum[b[x]])<=sum[mid]*2) { r=mid-1;continue;}
	if (X-1>=x+1&&-query(x+1,X-1,0)-(a[x]+sum[b[x]])>=sum[mid]*2) { r=mid-1;continue;}
	l=mid;
    }
    return l;
}
int dis(int x,int y)
{
	if (b[x]>y) return a[x]+sum[b[x]]-sum[y];
		else return a[x]+sum[y]-sum[b[x]];
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=2;i<=n;i++) { scanf("%d",&S[i]);sum[i]=sum[i-1]+S[i];}

    while (m--)
    {
        scanf("%d",&K);
        for (int i=1;i<=K;i++) scanf("%d%d",&Q[i].x,&Q[i].l);
        sort(Q+1,Q+K+1,cmp);
        for (int i=1;i<=K;i++) a[i]=Q[i].l,b[i]=Q[i].x;
        pre();
        ll ans=0;
        for (int i=1;i<=K;i++)
        {
            int L=b[i],R=b[i];
            if (b[i]!=1) L=erfenL(1,b[i],i);
            if (b[i]!=n) R=erfenR(i,n,i);
            ans+=R-L+1;
	    int pos=R+R-b[i];
	    if (pos<=n)
	    {
		    pos=lower_bound(b+1,b+K+1,pos)-b;
		    if (pos!=i&&b[pos]==R+R-b[i]&&dis(i,R)>=dis(pos,R)) ans--;
	    }
	    pos=L+L-b[i];
	    if (pos>=1)
	    {
		    pos=lower_bound(b+1,b+K+1,pos)-b;
		    if (pos!=i&&b[pos]==L+L-b[i]&&dis(i,L)>dis(pos,L)) ans--;
	    }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
