#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<bitset>
using namespace std;
const int N=100010;
int n,Q,flag[N],tot,prime[N],mu[N];
bitset<7005>a[N],b[N];
void pre(int n)
{
	mu[1]=1;
	for (int i=2;i<=n;i++)
	{
		if (!flag[i]) { prime[++tot]=i;mu[i]=-1;}
		for (int j=1;j<=tot&&i*prime[j]<=n;j++)
		{
			flag[i*prime[j]]=1;
			if (i%prime[j]==0) { mu[i*prime[j]]=0;break;}
				else mu[i*prime[j]]=-mu[i];
		}
	}
}
int main()
{
	scanf("%d%d",&n,&Q);
	pre(7000);
	for (int i=1;i<=n;i++)
		for (int j=1;j*i<=7000;j++) b[i][j*i]=(mu[j]%2+2)%2;
	for (int i=1;i<=n;i++) a[i]=0;
	while (Q--)
	{
		int id,x,v,y,z;
		scanf("%d",&id);
		if (id==1)
		{
			scanf("%d%d",&x,&v);
			a[x]=0;
			for (int i=1;i*i<=v;i++)
				if (v%i==0) a[x][i]=a[x][v/i]=1;
		}
		if (id==2)
		{
			scanf("%d%d%d",&x,&y,&z);
			a[x]=a[y]^a[z];
		}
		if (id==3)
		{
			scanf("%d%d%d",&x,&y,&z);
			a[x]=a[y]&a[z];
		}
		if (id==4)
		{
			scanf("%d%d",&x,&v);
			int ans=(a[x]&b[v]).count();
			if (ans<0) ans=-ans;
			printf("%d",ans&1);
		}
	}
	return 0;
}
