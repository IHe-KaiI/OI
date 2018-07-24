#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#define Abs(x) ((x>0)?(x):-(x))
using namespace std;
int n,m,Time[10010],x[10010],y[10010],f[10010];
int main()
{
	scanf("%d%d",&n,&m);
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&Time[i],&x[i],&y[i]);
		f[i]=1;
		for (int j=1;j<i;j++)
			if (Abs(x[i]-x[j])+Abs(y[i]-y[j])<=Time[i]-Time[j]) f[i]=max(f[i],f[j]+1);
		ans=max(ans,f[i]);
	}
	printf("%d\n",ans);
	return 0;
}
