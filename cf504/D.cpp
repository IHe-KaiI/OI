#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=200010;
int n,Q,a[N],last[N],f[N];
int lowbit(int x) { return x&(-x);}
int get(int x)
{
	int ans=0;
	for (int i=x;i>=1;i-=lowbit(i)) ans=max(ans,f[i]);
	return ans;
}
void add(int x,int y)
{
	for (int i=x;i<=Q;i+=lowbit(i)) f[i]=max(f[i],y);
}
int main()
{
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	if (a[i])
	{
		if (last[a[i]]==0) last[a[i]]=i;
		if (get(a[i])>last[a[i]]) { puts("NO");return 0;}
		last[a[i]]=i;
		add(a[i],i);
	}
	bool flag=0;
	for (int i=1;i<=n;i++)
		if (a[i]==0||a[i]==Q) { flag=1;break;}
	if (!flag) { puts("NO");return 0;}
	flag=0;
	for (int i=1;i<=n;i++)
		if (a[i]==Q) { flag=1;break;}
	a[0]=1;
	for (int i=1;i<=n;i++)
	if (!a[i])
	{
		if (!flag) a[i]=Q,flag=1;
			else a[i]=a[i-1];
	}
	puts("YES");
	for (int i=1;i<=n;i++) printf("%d%c",a[i]," \n"[i==n]);
	return 0;
}


