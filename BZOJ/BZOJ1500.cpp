#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
const int N=500100;
int n,m,a[N],id[N],root,tot,top,stack[N];
char s[20];
struct SPLAY
{
    int fa[N],size[N],Tree[N],rev[N],Sum[N],L_Max[N],R_Max[N],Max[N],lazy[N],son[N][2];
    void Clear(int x)
    {
        if (!x) return;
        fa[x]=size[x]=Tree[x]=rev[x]=Sum[x]=0;
        L_Max[x]=R_Max[x]=Max[x]=0;
        lazy[x]=1<<29;
        Clear(son[x][0]);
        Clear(son[x][1]);
        son[x][0]=son[x][1]=0;
        stack[++top]=x;
    }
    void update(int x)
    {
        if (!x) return;
        int l=son[x][0],r=son[x][1];
        Sum[x]=Tree[x];
        size[x]=1;
        L_Max[x]=R_Max[x]=(Tree[x]>0)?Tree[x]:0;
		Max[x]=Tree[x];
        if (l)
		{
			Sum[x]+=Sum[l];
			size[x]+=size[l];
			L_Max[x]=L_Max[l];
			Max[x]=max(Max[x],Max[l]);
		}	
        if (r)
		{
			Sum[x]+=Sum[r];
			size[x]+=size[r];
			R_Max[x]=R_Max[r];
			Max[x]=max(Max[x],Max[r]);
		}
		L_Max[x]=max(L_Max[l],Sum[l]+Tree[x]+L_Max[r]);
		R_Max[x]=max(R_Max[r],Sum[r]+Tree[x]+R_Max[l]);
		Max[x]=max(Max[x],Tree[x]+R_Max[l]+L_Max[r]);
    }
    void downdate(int x)
    {
        if (!x) return;
        if (lazy[x]!=1<<29)
        {
            int l=son[x][0],r=son[x][1];
            if (l)
            {
                lazy[l]=lazy[x];
                Tree[l]=lazy[x];
                Sum[l]=size[l]*lazy[x];
                Max[l]=(lazy[x]>0)?lazy[x]*size[l]:lazy[x]; 
                L_Max[l]=R_Max[l]=(lazy[x]>0)?lazy[x]*size[l]:0;
            }
            if (r)
            {
                lazy[r]=lazy[x];
                Tree[r]=lazy[x];
                Sum[r]=size[r]*lazy[x];
                Max[r]=(lazy[x]>0)?lazy[x]*size[r]:lazy[x]; 
                L_Max[r]=R_Max[r]=(lazy[x]>0)?lazy[x]*size[r]:0;
            }
            lazy[x]=1<<29;
        }
        if (rev[x])
        {
        	int l=son[x][0],r=son[x][1];
            swap(son[l][0],son[l][1]);
            swap(son[r][0],son[r][1]);
            swap(L_Max[l],R_Max[l]);
            swap(L_Max[r],R_Max[r]);
            rev[l]^=1;
            rev[r]^=1;
            rev[x]=0;
        }
    }
    void Rotate(int x,int &k)
    {
        int y=fa[x],z=fa[y],l,r;
        if (x==son[y][0]) l=0;else l=1;
        r=l^1;
        if (y==k) k=x;
        else
        {
            if (son[z][0]==y) son[z][0]=x;else son[z][1]=x;
        }
        fa[x]=z;fa[y]=x;fa[son[x][r]]=y;
        son[y][l]=son[x][r];son[x][r]=y;
        update(y);update(x);
    }
    void splay(int x,int &k)
    {
        while (x!=k)
        {
            int y=fa[x],z=fa[y];
            if (y!=k)
            {
                if ((son[z][0]==y)^(son[y][0]==x)) Rotate(x,k);
                    else Rotate(y,k);
            }
            Rotate(x,k);
        }
    }
    void build(int l,int r,int father)
    {
        if (l>r) return;
        if (l==r)
        {
            int i=id[l];
            fa[i]=id[father];
            son[id[father]][l>=father]=i;
            size[i]=1;
            Tree[i]=a[l];
            lazy[i]=1<<29;
            rev[i]=0;
            Sum[i]=a[l];
            L_Max[i]=R_Max[i]=(a[l]>0)?a[l]:0;
			Max[i]=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid-1,mid);
        build(mid+1,r,mid);
        int i=id[mid];
        fa[i]=id[father];
        son[id[father]][mid>=father]=i;
        size[i]=1;
        Tree[i]=a[mid];
        lazy[i]=1<<29;
        rev[i]=0;
        Sum[i]=a[mid];
        L_Max[i]=R_Max[i]=(a[mid]>0)?a[mid]:0;
		Max[i]=a[mid];
        update(i);
    }
    int find(int x)
    {
        int i=root;
        while (i)
        {
            downdate(i);
            if (size[son[i][0]]+1==x) return i;
            if (size[son[i][0]]>=x) i=son[i][0];
                else x-=size[son[i][0]]+1,i=son[i][1];
        }
    }
    int split(int x,int y)
    {
        int i=find(x),j=find(y);
        splay(i,root);
        splay(j,son[i][1]);
        return j;
    }
    void Insert(int i,int j)
    {
        int x=split(i,i+1);
        build(1,j,0);
        fa[id[(j+1)>>1]]=x;
        son[x][0]=id[(j+1)>>1];
        update(x);
        update(fa[x]);
    }
    void Del(int i,int j)
    {
        int x=split(i-1,j+1);
        int ID=son[x][0];
        Clear(ID);
        son[x][0]=0;
        update(x);
        update(fa[x]);
    }
    void Change(int i,int j,int X)
    {
        int x=split(i-1,j+1),y=son[x][0];
        lazy[y]=X;
        Tree[y]=X;
        L_Max[y]=R_Max[y]=(X>0)?X*size[y]:0;
		Max[y]=(X>0)?X*size[y]:X;
        Sum[y]=X*size[y];
        update(x);
        update(fa[x]);
    }
    void Reverse(int x,int y)
    {
        int i=split(x-1,y+1);
        rev[son[i][0]]^=1;
        swap(son[son[i][0]][0],son[son[i][0]][1]);
        swap(L_Max[son[i][0]],R_Max[son[i][0]]);
        update(i);
        update(fa[i]);
    }
    int Get_Sum(int x,int y)
    {
        int i=split(x-1,y+1);
        return Sum[son[i][0]];
    }
    int Get_Max(int x,int y)
    {
        int i=split(x-1,y+1);
        return Max[son[i][0]];
    }
}Splay;
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=2;i<=n+1;i++) scanf("%d",&a[i]),id[i]=i;
    id[1]=1;id[n+2]=n+2;
    Splay.build(1,n+2,0);
    root=(n+3)>>1;
    tot=n+2;
    top=0;
	while (m--)
    {
        int Start,Num;
        scanf("%s",s+1);
        if (s[1]=='I')
        {
            scanf("%d%d",&Start,&Num);
            for (int i=1;i<=Num;i++)
            {
                scanf("%d",&a[i]);
                if (top) id[i]=stack[top--];
                    else id[i]=++tot;
            }
            Start++;
            Splay.Insert(Start,Num);
        }
        if (s[1]=='D') scanf("%d%d",&Start,&Num),Start++,Splay.Del(Start,Start+Num-1);
        if (s[1]=='M'&&s[3]=='K')
        {
            int x;
            scanf("%d%d%d",&Start,&Num,&x);
            Start++;
            Splay.Change(Start,Start+Num-1,x);
        }
        if (s[1]=='R') scanf("%d%d",&Start,&Num),Start++,Splay.Reverse(Start,Start+Num-1);
        if (s[1]=='G') scanf("%d%d",&Start,&Num),Start++,printf("%d\n",Splay.Get_Sum(Start,Start+Num-1));
        if (s[1]=='M'&&s[3]=='X') printf("%d\n",Splay.Get_Max(2,Splay.size[root]-1));
    }
    return 0;
}
