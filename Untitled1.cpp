
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct drink{
	int v,w;
}; 

int main() {
    int n, m;
    cin >> n >> m;
    vector<drink> d;
    d.resize(n+1);
    for(int i=1;i<=n;i++){
    	cin>>d[i].v>>d[i].w;
	}
	
	vector<vector<int> > dp(n+1, vector<int>(m+1, 0));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(d[i].v>j){
				dp[i][j]=dp[i-1][j];
			}else{
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-d[i].v]+d[i].w);
			}
		}
	}
    
    cout<<dp[n][m]<<endl;
	cout<<"try to do a change"<<endl;
	//一个分支
    return 0;
}









