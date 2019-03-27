#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=100010;
int n,a[N],Min[N*32],Max[N*32],son[N*32][2],f[N],cnt,root,Ans,number;
pair<int,int>A[N];
int read()
{
	int x=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x;
}
int get(int x) 
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
void newnode(int &x)
{
	x=++cnt;
	son[cnt][0]=son[cnt][1]=0;
	Max[cnt]=-(1<<29);
	Min[cnt]=1<<29;
}
void Insert(int id,int y,int z)
{
	for (int i=30;i>=0;i--)
	{
		int bit=(y>>i)&1;
		if (!son[id][bit]) newnode(son[id][bit]);
		id=son[id][bit];
		Max[id]=max(Max[id],z);Min[id]=min(Min[id],z);
	}
}
void query(int id,int y,int z)
{
	for (int i=30;i>=0;i--)
	{
		int bit=(y>>i)&1;
		if (son[id][bit]&&(Max[son[id][bit]]!=z||Min[son[id][bit]]!=z)) id=son[id][bit];
		else
		{
			id=son[id][bit^1];
			Ans+=1<<i;
		}
	}
	if (Max[id]==z) number=Min[id];
		else number=Max[id];
}
int main()
{
	freopen("secret.in","r",stdin);
	freopen("secret.out","w",stdout);
	scanf("%d",&n);
	Min[0]=1<<29;Max[0]=-(1<<29);
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		a[i]=a[i]^a[i-1];
	}
	for (int i=0;i<=n;i++) f[i]=i;
	ll ans=0;
	while (1)
	{
		int num=0;
		for (int i=0;i<=n;i++)
			if (get(i)==i) num++;
		if (num==1) break;
		cnt=root=0;
		newnode(root);
		for (int i=0;i<=n;i++) Insert(root,a[i],get(i)),A[i]=make_pair((1LL<<31)-1,1<<29);
		for (int i=0;i<=n;i++)
		{
			Ans=0;number=0;
			int X=get(i);
			query(root,a[i],X);
			A[X]=min(A[X],make_pair(Ans,number));
		}
		for (int i=1;i<=n;i++)
		if (get(f[i])==i)
		{
			int x=get(A[i].second);
			if (x==i) continue;
			ans+=A[i].first;
			f[x]=i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
