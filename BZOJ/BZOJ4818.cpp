#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define mo 20170408
#define ll long long
using namespace std;
const int N=105;
int n,m,p,tot,prime[2000010],num[N];
bool flag[20000010];
struct matrix
{
	int a[N][N];
	int* operator [] (int x) { return a[x];}
	matrix() { memset(a,0,sizeof(a));}
	matrix operator * (const matrix b)
	{
		matrix c;
		for (int i=0;i<p;i++)
			for (int j=0;j<p;j++)
				for (int k=0;k<p;k++) (c[i][j]+=(ll)a[i][k]*b.a[k][j]%mo)%=mo;
		return c;
	}
}f,g,F;
matrix mi(matrix x,int y)
{
	matrix ans;
	for (int i=0;i<p;i++) ans[i][i]=1;
	while (y)
	{
		if (y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}
void Get_Prime()
{
	for (int i=2;i<=m;i++)
	{
		if (!flag[i]) prime[++tot]=i;
		for (int j=1;j<=tot;j++)
		{
			if (prime[j]*i>m) break;
			flag[prime[j]*i]=1;
			if (!i%prime[j]) break;
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	Get_Prime();
	for (int i=1;i<=m;i++) num[i%p]++;
	for (int i=0;i<p;i++)
		for (int j=0;j<p;j++) g[i][j]=num[(j-i+p)%p];
	f[0][0]=1;
	f=mi(g,n)*f;
	for (int i=1;i<=tot;i++) num[prime[i]%p]--;
	for (int i=0;i<p;i++)
		for (int j=0;j<p;j++) g[i][j]=num[(j-i+p)%p];
	F[0][0]=1;
	F=mi(g,n)*F;
	printf("%d\n",(f[0][0]-F[0][0]+mo)%mo);
	return 0;
}
