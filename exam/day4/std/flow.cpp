#include<bits/stdc++.h>
using namespace std;
 
int T, n, a, b;

int realmain(){
	scanf("%d%d%d",&n,&a,&b);
	if (a==1) return puts("0"), 0;
	
	if (n==2){
		if (a%2) return puts("0"), 0;
		if (b%2&&a==0) return puts("0"), 0;
		puts(a+b>=2? "1": "0");
	}else{
		puts(a+b>=n+1||a==n||b==n? "1": "0"); 
	}
}
int Test; 
int main(){
	freopen("flow.in","r",stdin);
	freopen("flow.out","w",stdout);
	cin>>Test;
	for (cin>>T;T--;){
		realmain();
	}
}
