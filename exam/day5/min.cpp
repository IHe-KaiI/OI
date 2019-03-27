#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	return 0;
}
