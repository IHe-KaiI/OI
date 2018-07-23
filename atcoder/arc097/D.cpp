#include<bits/stdc++.h>
using namespace std;
int n,m,a[100010],f[100010];
int get(int x)
{
	if (f[x]==x) return x;else f[x]=get(f[x]);
	return f[x];
}
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		f[i]=i;
	}
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		f[get(x)]=get(y);
	}
	int ans=0;
	for (int i=1;i<=n;i++)
		if (get(i)==get(a[i])) ans++;
	printf("%d\n",ans);
	return 0;
}
