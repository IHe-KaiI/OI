#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define ll long long
using namespace std;
const int N=100010;
int n,m,a[N],Min[N*20],Max[N*20],son[N*20][2],f[N],cnt,root;
pair<int,int>A[N];
int get(int x) 
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
void up(int id)
{
	Max[id]=max(Max[son[id][0]],Max[son[id][1]]);
	Min[id]=min(Min[son[id][0]],Min[son[id][1]]);
}
void Insert(int &id,int x,int y,int z)
{
	if (!id) { id=++cnt;son[id][0]=son[id][1]=0;Max[id]=-(1<<29);Min[id]=1<<29;}
	if (x<0) { Max[id]=max(Max[id],z);Min[id]=min(Min[id],z);return;}
	Insert(son[id][(y>>x)&1],x-1,y,z);
	up(id);
}
pair<int,int> query(int id,int x,int y,int z)
{
	if (!id||(Max[id]==z&&Min[id]==z)) return make_pair(0,0);
	if (x<0)
	{
		if (Max[id]==z) return make_pair(0,Min[id]);
			else return make_pair(0,Max[id]);
	}
	int bit=(y>>x)&1;
	if (bit==1)
	{
		if (son[id][bit]&&(Max[son[id][bit]]!=z||Min[son[id][bit]]!=z))
		{
			pair<int,int> X=query(son[id][bit],x-1,y,z);
			return make_pair(X.first+(1<<x),X.second);
		}
	}
	return max(query(son[id][bit],x-1,y,z),query(son[id][bit^1],x-1,y,z));
}
int main()
{
	scanf("%d%d",&n,&m);
	Min[0]=1<<29;Max[0]=-(1<<29);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
	}
	for (int i=1;i<=n;i++) f[i]=i;
	ll ans=0;
	while (1)
	{
		int num=0;
		for (int i=1;i<=n;i++)
			if (get(i)==i) num++;
		if (num==1) break;
		cnt=root=0;
		for (int i=1;i<=n;i++) Insert(root,m,a[i],get(i)),A[i]=make_pair(0,0);
		for (int i=1;i<=n;i++)
		{
			pair<int,int> x=query(root,m,a[i],get(i));
			A[get(i)]=max(A[get(i)],x);
		}
		for (int i=1;i<=n;i++)
		if (get(f[i])==i)
		{
			int x=A[i].second;
			if (get(x)==i) continue;
			ans+=A[i].first;
			f[get(x)]=i;
		}
	}
	printf("%lld\n",ans);
	return 0;
}

