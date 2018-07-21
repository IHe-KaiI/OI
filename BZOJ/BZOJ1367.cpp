#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define Abs(x) (((x)>0)?(x):-(x))
#define ll long long
using namespace std;
const int N=1000100;
int n,a[N],number,cnt,son[N][2],dist[N],val[N],root[N],num[N],L[N],R[N],size[N];
void newnode(int x)
{
	cnt++;
	son[cnt][0]=son[cnt][1]=dist[cnt]=0;
	val[cnt]=x;
	size[cnt]=1;
}
int merge(int x,int y)
{
	if (!x||!y) return x^y;
	if (val[x]<val[y]) swap(x,y);
	son[x][1]=merge(son[x][1],y);
	size[x]=size[son[x][0]]+size[son[x][1]]+1;
	if (dist[son[x][1]]>dist[son[x][0]]) swap(son[x][0],son[x][1]);
	dist[x]=dist[son[x][1]]+1;
	return x;
}
void POP(int &x)
{
	x=merge(son[x][0],son[x][1]);
}
int main()
{
	scanf("%d",&n);
	dist[0]=-1;
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		a[i]-=i;
		newnode(a[i]);
		num[++number]=1;
		root[number]=cnt;
		L[number]=R[number]=i;
		while (number>1&&val[root[number]]<val[root[number-1]])
		{
			root[number-1]=merge(root[number-1],root[number]);
			num[number-1]+=num[number];
			while (size[root[number-1]]*2>num[number-1]+1) POP(root[number-1]);
			R[number-1]=R[number];
			number--;
		}
	}
	ll ans=0;
	for (int i=1;i<=number;i++)
	{
		for (int j=L[i];j<=R[i];j++) ans+=Abs(a[j]-val[root[i]]);
	}
	printf("%lld\n",ans);
	return 0;
}
