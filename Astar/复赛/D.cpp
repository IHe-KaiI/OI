#include<bits/stdc++.h>
#define mo 1000000007
using namespace std;
int T,K,n,a[6][1010],f[500010],tot;
struct node{int i,j,k,l,x;}A[500010];
void Get()
{
	int i=0,j=0,k=0,l=0,x=0;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
		if (a[1][i]==a[2][j])
		{
			if (K==2)
			{
				A[++tot]=(node){i,j,k,l,x};
			}else
			{
				for (k=1;k<=n;k++)
				if (a[1][i]==a[3][k])
				{
					if (K==3)
					{
						A[++tot]=(node){i,j,k,l,x};
					}else
					{
						for (l=1;l<=n;l++)
						if (a[1][i]==a[4][l])
						{
							if (K==4)
							{
								A[++tot]=(node){i,j,k,l,x};
							}else
							{
								for (x=1;x<=n;x++)
									if (a[1][i]==a[5][x]) A[++tot]=(node){i,j,k,l,x};
								
							}
						}
					}
				}
			}
		}
}
bool cmp(node a,node b)
{
	if (a.i!=b.i) return a.i<b.i;
	if (a.j!=b.j) return a.j<b.j;
	if (a.k!=b.k) return a.k<b.k;
	if (a.l!=b.l) return a.l<b.l;
	return a.x<b.x;
}
int main()
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&K,&n);
		for (int i=1;i<=K;i++)
			for (int j=1;j<=n;j++) scanf("%d",&a[i][j]);
		tot=0;
		Get();
		sort(A+1,A+tot+1,cmp);
		A[0]=(node){0,0,0,0,0};
		f[0]=1;
		for (int i=1;i<=tot;i++) f[i]=0;
		for (int i=1;i<=tot;i++)
		{
			for (int j=0;j<i;j++)
			{
				if (A[j].i!=0&&A[j].i>=A[i].i) continue;
				if (A[j].j!=0&&A[j].j>=A[i].j) continue;
				if (A[j].k!=0&&A[j].k>=A[i].k) continue;
				if (A[j].l!=0&&A[j].l>=A[i].l) continue;
				if (A[j].x!=0&&A[j].x>=A[i].x) continue;
				f[i]=(f[i]+f[j])%mo;
			}
		}
		int ans=0;
		for (int i=1;i<=tot;i++) ans=(ans+f[i])%mo;
		printf("%d\n",ans);
	}
	return 0;
}
