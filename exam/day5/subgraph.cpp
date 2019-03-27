#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<unordered_map>
#define ll long long
#define mo 1000000007
using namespace std;
const int N=100010,M=200010;
int n,m,K,A[N],vis[N];
struct node{int x,y;}a[M];
vector<int>E[N];
unordered_map<int,bool>S[N];
bool check(int x,int y)
{
	return S[x][y];
}
ll Get()
{
	ll ans=0;
	int B=sqrt(m),cnt=0;
	for (int i=1;i<=n;i++)
	if (E[i].size()<=B)
	{
		vis[i]=1;
		for (int j=0;j<E[i].size();j++)
		if (!vis[E[i][j]])
			for (int k=j+1;k<E[i].size();k++)
			if (!vis[E[i][k]])
				if (check(E[i][j],E[i][k])) ans++;
	}else A[++cnt]=i;
	for (int i=1;i<=cnt;i++)
		for (int j=i+1;j<=cnt;j++)
			for (int k=j+1;k<=cnt;k++)
			if (check(A[i],A[j])&&check(A[i],A[k])&&check(A[j],A[k])) ans++;
	return ans%mo;	
}
ll mi(ll x,int y)
{
	ll ans=1;
	while (y)
	{
		if (y&1) ans=ans*x%mo;
		x=x*x%mo;
		y>>=1;
	}
	return ans;
}
int main()
{
//	freopen("subgraph.in","r",stdin);
//	freopen("subgraph.out","w",stdout);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		S[x][y]=S[y][x]=1;
		E[x].push_back(y);
		E[y].push_back(x);
		a[i]=(node){x,y};
	}
	if (K==1)
	{
		printf("%d\n",m);
		return 0;
	}
	if (K==2)
	{
		int ans=0;
		for (int i=1;i<=m;i++)
		{
			ans=(ans+E[a[i].x].size()-1)%mo;
			ans=(ans+E[a[i].y].size()-1)%mo;
		}
		ans=(ll)ans*mi(2,mo-2)%mo;
		printf("%d\n",ans);
		return 0;
	}
	if (K==3)
	{
		ll ans=0;
		for (int i=1;i<=m;i++)
		{
			ans=(ans+(ll)(E[a[i].x].size()-1)*(E[a[i].y].size()-1)%mo)%mo;
		}
		printf("%lld\n",(ans-Get()*2%mo+mo)%mo);
		return 0;
	}
	printf("%lld\n",(ll)m*(m-1)%mo*(m-2)%mo*mi(6,mo-2)%mo);
	return 0;
}
