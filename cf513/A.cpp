#include<iostream>
#include<cstdio> 
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n;
int main()
{
	scanf("%d",&n);
	int tot=0,x;
	for (int i=1;i<=n;i++)
	{
		scanf("%1d",&x);
		if (x==8) tot++;
	}
	printf("%d\n",min(tot,n/11));
	return 0;
}
