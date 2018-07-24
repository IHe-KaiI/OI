#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
int n,m,tot,root[600010],Sum[18000010][2],son[18000010][2];
void Insert(int &id,int last,int x,int y)
{
	if (y<0) return;
	id=++tot;
	son[id][0]=son[last][0];
	son[id][1]=son[last][1];
	int num=(x&(1<<y))>>y;
	Insert(son[id][num],son[last][num],x,y-1);
	Sum[id][num]=Sum[last][num]+1;
	Sum[id][num^1]=Sum[last][num^1];
}
int query(int l,int r,int x,int y)
{
	if (y<0) return 0;
	int num=(x&(1<<y))>>y;
	if (Sum[r][num^1]-Sum[l][num^1]) return query(son[l][num^1],son[r][num^1],x,y-1)+(1<<y);
		else return query(son[l][num],son[r][num],x,y-1);
}
int main()
{
	scanf("%d%d",&n,&m);
	int ALL=0,cnt=n+1;
	Insert(root[1],root[0],0,29);
	for (int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		ALL^=x;
		Insert(root[i+1],root[i],ALL,29);
	}
	for (int i=1;i<=m;i++)
	{
		char s[5];int l,r,x;
		scanf("%s",s);
		if (s[0]=='A')
		{
			scanf("%d",&x);
			cnt++;
			ALL^=x;
			Insert(root[cnt],root[cnt-1],ALL,29);
		}else
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",query(root[l-1],root[r],x^ALL,29));
		}
	}
	return 0;
}
