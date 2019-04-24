#include <cstdio>
#include <cstring>
int n;
char s[10010];
struct data
{
    int v[810][810];
    data() {memset(v , 0 , sizeof(v));}
    int *operator[](int a) {return v[a];}
    data operator*(data &a)
    {
        data ans;
        int i , j , k;
        for(i = 0 ; i <= n ; i ++ )
            for(k = 0 ; k <= n ; k ++ )
                for(j = 0 ; j <= n ; j ++ )
                    ans[i][j] = (ans[i][j] + (long long)v[i][k] * a[k][j]%998244353) % 998244353;
        return ans;
    }
}A;
data pow(data x , int y)
{
    data ans;
    int i;
    for(i = 0 ; i <= n ; i ++ ) ans[i][i] = 1;
    while(y)
    {
        if(y & 1) ans = ans * x;
        x = x * x , y >>= 1;
    }
    return ans;
}
int main()
{
    int m , k=0 , i , x , y , ans = 0;
    scanf("%d%d" , &n , &m);
    for(i = 1 ; i <= m ; i ++ ) scanf("%d%d" , &x , &y) , A[x][y] = A[y][x] = 1;
    for(i = 1 ; i <= n ; i ++ ) A[i][i] = A[i][0] = 1;
    A[0][0] = 1;
    scanf("%s" , s) ;
    int l=strlen(s);
    for (int i=l-1;i>=0;i--) k=k*2+(s[i]-'0');
    A = pow(A , k);
    for(i = 0 ; i <= n ; i ++ ) ans = (ans + A[1][i]) % 998244353;
    printf("%d\n" , ans);
    return 0;
}
