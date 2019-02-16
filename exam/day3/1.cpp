#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<set>
using namespace std;
const int N=1000010;
int n,a[N],Q,son[N*31][2],Max[N*31],Min[N*31],num[N*31],ans[35][5],dep[N*31],fa[N*31],cnt,pos[N],flag1,flag2,ID[N*31],V;
set<int>S[N+N];
int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9') { if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9') { x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void check(int id,int d)
{
	if (num[son[id][0]]&&num[son[id][1]])
	{
		int x=son[id][0],y=son[id][1];
		flag1=flag2=0;
		if (Max[x]<Min[y]) flag1=1;
		if (Min[x]>Max[y]) flag2=2;
		if (flag1+flag2==0) flag1=3;
		ans[dep[id]][flag1+flag2]+=d;
	}
}
void Insert(int X)
{
	int id=1,x=a[X];
	for (int i=30;i>=0;i--)
	{
		int bit=(x>>i)&1;
		if (!son[id][bit]) son[id][bit]=++cnt,dep[cnt]=i-1,fa[cnt]=id,Max[cnt]=0,Min[cnt]=1<<29;
		id=son[id][bit];
	}
	if (!ID[id]) ID[id]=++V;
	S[V].insert(X);
	pos[X]=id;
	for (int i=fa[id];i;i=fa[i]) check(i,-1);
	for (;id;id=fa[id])
	{
		num[id]++;
		if (!son[id][0]&&!son[id][1])
		{
			Max[id]=max(Max[id],X);
			Min[id]=min(Min[id],X);
			continue;
		}
		Max[id]=max(Max[son[id][0]],Max[son[id][1]]);
		Min[id]=min(Min[son[id][0]],Min[son[id][1]]);
		check(id,1);
	}
}
void write(int x)
{
	if (x<10) { putchar('0'+x);return;}
	write(x/10);
	putchar('0'+x%10);
}
void calc_ans()
{
	int Ans=0;
	for (int i=0;i<=30;i++)
	{
		if (ans[i][3]||(ans[i][1]&&ans[i][2])) { Ans=-1;break;}
		if (ans[i][2]) Ans+=1<<i;
	}
//	write(Ans);
}
void del(int id,int x)
{
	S[ID[id]].erase(x);
	int MIN,MAX;
	if (!S[ID[id]].empty())
	{
		MIN=*(S[ID[id]].begin());
		MAX=*(--S[ID[id]].end());
	}else MIN=1<<29,MAX=0;
	for (int i=fa[id];i;i=fa[i]) check(i,-1);
	Min[id]=MIN;Max[id]=MAX;
	num[id]--;
	for (id=fa[id];id;id=fa[id])
	{
		num[id]--;
		Max[id]=max(Max[son[id][0]],Max[son[id][1]]);
		Min[id]=min(Min[son[id][0]],Min[son[id][1]]);
		check(id,1);
	}
}
int main()
{
	freopen("sort.in","r",stdin);
	freopen("sort.out","w",stdout);
	scanf("%d",&n);
	dep[++cnt]=30;
	Max[0]=0;Min[0]=1<<29;
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		Insert(i);
	}
	calc_ans();
	scanf("%d",&Q);
	while (Q--)
	{
		int x=read(),y=read();
		del(pos[x],x);
		a[x]=y;
		Insert(x);
		calc_ans();
	}
	return 0;
}
