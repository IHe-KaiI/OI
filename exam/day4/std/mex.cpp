#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef __int128 LL;
const int mo=998244353;
const int inv2=499122177;
const int inv6=166374059;
const int inv4=748683265;
const int inv30=432572553;
LL l,r;
char s[100];
__int128 Read() {
    __int128 x=0;
    scanf("%s",s);
    int len=strlen(s);
    for (int i=0;i<len;i++)
        x=x*10+s[i]-48;
    return x;
}
int Sum(int x,int y) {
    x+=y;
    return (x>=mo)?x-mo:x;
}
int Sub(int x,int y) {
    x-=y;
    return (x<0)?x+mo:x;
}
int Mul(int x,int y) {
    return (long long)x*y%mo;
}
LL Ex_Sqrt(LL x,int ty) {
    LL l=0,r=2e18;
    while (l<r) {
        LL mid=(l+r+1)/2;
        LL nowf=mid*mid;
        if (ty==1) nowf-=mid+1;
        else if (ty==2) nowf+=mid;
        if (nowf<=x) l=mid;
        else r=mid-1;
    }
    return l;
}
int T(int x,int ty) {
    if (ty==1) return Mul(Mul(x,Sum(x,1)),inv2);
    if (ty==2) return Mul(Mul(Mul(x,Sum(x,1)),Sum(Sum(x,x),1)),inv6);
    if (ty==3) return Mul(Mul(Mul(x,x),Mul(Sum(x,1),Sum(x,1))),inv4);        
    int nowx=Sub(Mul(3,Sum(Mul(x,x),x)),1);
    return Mul(Mul(Mul(x,Mul(Sum(x,1),Sum(Sum(x,x),1))),nowx),inv30);
}
namespace task1 {
    int F1(LL n) {
        LL nx=Ex_Sqrt(n,0)%mo;
        int nown=n%mo;
        int ans=Mul(nown,Mul(Sum(nown,1),nx));
        ans=Sum(Sub(ans,Mul(T(nx,2),Sum(Sum(nown,nown),1))),T(nx,4));
        return Mul(ans,inv2);
    }
    int F2(LL k) {
        int nowk=Ex_Sqrt(k,0)%mo;
        return Sub(Mul(k%mo,nowk),T(nowk,2));
    }
    int Get(LL k,LL n) {
        if (k*k-k>n) return 0;
        LL lx=k*k-n;
        return Sub(Sum(Mul(k%mo,(k-lx+1)%mo),F2(k)),F2(lx-1));
    }
    int Solve(LL n) {
        LL nx=Ex_Sqrt(n+1,0);
        return Sum(Sum(T(nx%mo,2),F1(nx)),Get(nx+1,n));
    }
}
namespace task2 {
    int F1(LL n) {
        LL nx=Ex_Sqrt(n,2)%mo;
        int nown=n%mo;
        int ans=Sum(T(nx,4),Mul(2,T(nx,3)));
        ans=Sub(ans,Mul(Sum(nown,Sub(nown,2)),T(nx,2)));
        ans=Sub(ans,Mul(Sum(nown,Sub(nown,1)),T(nx,1)));
        ans=Sum(ans,Mul(Mul(nown,Sub(nown,1)),nx));
        return Mul(ans,inv2);
    }
    int F2(LL k) {
        LL nowk=Ex_Sqrt(k,2)%mo;
        return Sub(Mul(k%mo,nowk),Sum(T(nowk,2),T(nowk,1)));
    }
    int Get(LL k,LL n) {
        if ((k-1)*(k-1)>n) return 0;
        LL lx=k*k-k-n;
        return Sub(Sum(Mul(k%mo,(k-lx)%mo),F2(k-1)),F2(lx-1));
    }
    int Solve(LL n) {
        LL nx=Ex_Sqrt(n,1);
        return Sum(Sum(Sub(T(nx%mo,2),T(nx%mo,1)),F1(nx)),Get(nx+1,n));
    }
}
int Solve(LL n) {
    return Sum(task1::Solve(n),task2::Solve(n));
}
int t,Test;
int main() {
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
    scanf("%d%d",&Test,&t);
    while (t--) {
        l=Read();
        r=Read();
        printf("%d\n",Sub(Solve(r),Solve(l-1)));
    }
    return 0;
}
