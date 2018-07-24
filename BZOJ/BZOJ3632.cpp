#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,p[55][55],f[55];
bool In[55];
int main()
{
	scanf("%d",&n);
	srand(23333);
	int x,y;
	while (scanf("%d%d",&x,&y)!=EOF) p[x][y]=p[y][x]=1;
	for (int i=1;i<=n;i++) f[i]=i;
	int ans=0,T=0;
	while (T<=60000)
	{
		T++;
		random_shuffle(f+1,f+n+1);
		memset(In,0,sizeof(In));
		int tot=0;
		for (int i=1;i<=n;i++)
		{
			int u=f[i];
			bool flag=1;
			for (int j=1;j<=n;j++)
				if (!p[j][u]&&In[j]) { flag=false;break;}
			if (flag) { tot++;In[u]=1;}
		}
		ans=max(ans,tot);
	}
	printf("%d\n",ans);
	return 0;
}
