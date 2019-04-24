#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,m,p[5010][5010],K;
ll rd() { return (ll)rand()%2333*rand();}
int main()
{
		freopen("1.in","w",stdout);
		srand(time(NULL));
	//	n=30;m=100;K=25;//task1
	//	n=500;m=2000;K=15;//task2
	//	n=500;m=2000;K=20;//task3
	//	n=3000;m=5000;K=100;//task 4
		n=500;m=2000;K=15;//duipai
		printf("%d %d\n",n,m);
		memset(p,0,sizeof(p));
		for (int i=1;i<=m;i++)
		{	
			int x=rd()%n+1,y=rd()%n+1;
			while (x==y||p[x][y]) x=rd()%n+1,y=rd()%n+1;
			p[x][y]=p[y][x]=1;
			printf("%d %d\n",x,y);
		}
		for (int i=1;i<K;i++) putchar('0'+rd()%2);
		putchar('1');
	return 0;
}
