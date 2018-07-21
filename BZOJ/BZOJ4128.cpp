#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,p;
struct matrix
{
	int x[75][75];
	matrix() { memset(x,0,sizeof(x));}
}P,a,b,HASH[200];
matrix operator * (matrix a,matrix b)
{
	matrix c;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) (c.x[i][1]+=a.x[i][j]*b.x[j][1]%p)%=p;
	return c;
}
bool check(matrix a,matrix b)
{
	for (int i=1;i<=n;i++)
		if (a.x[i][1]!=b.x[i][1]) return 0;
	return 1;
}
matrix mul(matrix &a,matrix b)
{
	matrix c;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++)
			for (int k=1;k<=n;k++) (c.x[i][j]+=a.x[i][k]*b.x[k][j])%=p;
	return c;
}
matrix mi(matrix x,int y)
{
	matrix ans;
	for (int i=1;i<=n;i++) ans.x[i][i]=1;
	while (y)
	{
		if (y&1) ans=mul(ans,x);
		x=mul(x,x);
		y>>=1;
	}
	return ans;
}
int BSGS()
{
	int m=ceil(sqrt(p));
	matrix A=P,B;
	HASH[0]=A;
	for (int i=1;i<=m;i++)
	{
		A=a*A;
		HASH[i]=b*A;
	}
	A=P;
	B=mi(a,m);
	for (int i=1;i<=m;i++)
	{
		A=B*A;
		for (int j=m;j>=0;j--)
			if (check(A,HASH[j])) return m*i-j;
	}
}
int main()
{
	scanf("%d%d",&n,&p);
	srand(23333);
	for (int i=1;i<=n;i++) P.x[i][1]=rand()%p;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) scanf("%d",&a.x[i][j]);
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++) scanf("%d",&b.x[i][j]);
	printf("%d\n",BSGS());
	return 0;
}
