#include<cstdio>
#include<cstring>
#define mo 2009
using namespace std;
int n,T;
struct matrix
{
	int a[100][100];
	matrix () { memset(a,0,sizeof(a));}
	matrix operator * (matrix A)
	{
		matrix C;
		for (int i=0;i<n*9;i++)
			for (int j=0;j<n*9;j++) C.a[i][j]=0;
		for (int i=0;i<n*9;i++)
			for (int j=0;j<n*9;j++)
				for (int k=0;k<n*9;k++)
				(C.a[i][j]+=a[i][k]*A.a[k][j])%=mo;
		return C;
	}
}A;
matrix mi(matrix x,int y)
{
	matrix ans;
	for (int i=0;i<n*9;i++) ans.a[i][i]=1;
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
	scanf("%d%d",&n,&T);
	for (int i=0;i<n;i++)
		for (int j=0;j<=7;j++) A.a[i+n*j][i+n*(j+1)]=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
		{
			int x;
			scanf("%1d",&x);
			if (x) A.a[i+n*(x-1)][j]=1;
		}
	printf("%d\n",mi(A,T).a[0][n-1]);
	return 0;
}
