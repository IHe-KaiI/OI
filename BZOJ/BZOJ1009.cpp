#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,K,s[30],fail[30];
struct matrix
{
	int x[30][30];
	matrix() { memset(x,0,sizeof(x));}
}ans,A;
matrix operator * (matrix a,matrix b)
{
	matrix c;
	for (int i=0;i<m;i++)
		for (int j=0;j<m;j++)
			for (int k=0;k<m;k++)
			(c.x[i][j]+=a.x[i][k]*b.x[k][j])%=K;
	return c;
}
void KMP()
{
	int j=0;
	for (int i=2;i<=m;i++)
	{
		while (j&&s[j+1]!=s[i]) j=fail[j];
		if (s[j+1]==s[i]) j++;
		fail[i]=j;
	}
}
matrix mi(matrix x,int y)
{
	ans.x[0][0]=1;
	while (y)
	{
		if (y&1) ans=ans*x;
		x=x*x;
		y>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;i++) scanf("%1d",&s[i]);
	KMP();
	for (int i=0;i<m;i++)
		for (int j=0;j<=9;j++)
		{
			int k=i;
			while (k&&s[k+1]!=j) k=fail[k];
			if (s[k+1]==j) k++;
			if (k!=m) A.x[i][k]=(A.x[i][k]+1)%K;
		}
	ans=mi(A,n);
	int Ans=0;
	for (int i=0;i<m;i++) (Ans+=ans.x[0][i])%=K;
	printf("%d\n",Ans);
	return 0;
}
