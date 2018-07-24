#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#define eps 1e-6
using namespace std;
int n,Stack[50010];
struct node{double x,y;int id;}a[50010];
bool cmp(node a,node b) { return (fabs(a.x-b.x)<=eps)?a.y<b.y:a.x>b.x;}
bool CMP(int x,int y) { return a[x].id<a[y].id;}
double calc(int i,int j)
{
	return (a[j].y-a[i].y)/(a[i].x-a[j].x);
}
int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n;i++) { scanf("%lf%lf",&a[i].x,&a[i].y);a[i].id=i;}
	sort(a+1,a+n+1,cmp);
	int top=2;
	Stack[1]=1;Stack[2]=2;
	for (int i=3;i<=n;i++)
	{
		if (fabs(a[Stack[top]].x-a[i].x)<=eps) top--;
		while (top>1&&calc(i,Stack[top])>=calc(Stack[top],Stack[top-1])) top--;
		Stack[++top]=i;
	}
	sort(Stack+1,Stack+top+1,CMP);
	for (int i=1;i<=top;i++) printf("%d ",a[Stack[i]].id);
	return 0;
}
