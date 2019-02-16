#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,A,B,C;
int main()
{
	freopen("diameter.in","r",stdin);
	freopen("diameter.out","w",stdout);
	scanf("%d",&n);
	A=0;
	for (int a=1;a<=5000;a++)
	{
		for (int b=0;b<=5000-a;b++)
		{
			int c=n-a*b;
			if (c%(a+b)==0&&c/(a+b)+a+b<=5000-4) { A=a;B=b;C=c/(a+b);break;}
		}
		if (A!=0) break;
	}
	if (C>B) swap(C,B);
	if (C>A) swap(C,A);
	if (B>A) swap(A,B);
	int num=1;
	if (A) num++;
	if (B) num++;
	if (C) num++;
	printf("%d\n",num+A+B+C);
	if (A) puts("1 2 1");
	if (B) puts("1 3 1");
	if (C) puts("1 4 1");
	int cnt=num;
	for (int i=1;i<=A;i++) printf("%d 2 1\n",++cnt);
	for (int i=1;i<=B;i++) printf("%d 3 1\n",++cnt);
	for (int i=1;i<=C;i++) printf("%d 4 1\n",++cnt);
	return 0;
}
