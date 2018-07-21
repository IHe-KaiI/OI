#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int sg[100010],flag[100010],F,n;
void pre()
{
	for (int i=F;i<=100000;i++)
	{
		for (int k=2,j;k<=i;k=j+1)
		{
			j=i/(i/k);
			int num1=k-(i%k),num2=i%k;
			flag[(sg[i/k]*(num1&1))^(sg[i/k+1]*(num2&1))]=i;
			if (k+1<=j)
			{
				num1=k+1-(i%(k+1));num2=i%(k+1);
				flag[(sg[i/k]*(num1&1))^(sg[i/k+1]*(num2&1))]=i;
			}
		}
		for (int j=0;j<=100000;j++)
			if (flag[j]!=i) { sg[i]=j;break;}
	}
}
int main()
{
	int T;
	scanf("%d%d",&T,&F);
	pre();
	while (T--)
	{
		scanf("%d",&n);
		int ans=0;
		for (int i=1;i<=n;i++)
		{
			int x;
			scanf("%d",&x);
			ans^=sg[x];
		}
		if (ans) printf("1%c"," \n"[T==0]);else printf("0%c"," \n"[T==0]);
	}
	return 0;
}
