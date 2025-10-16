#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct Edge{
	int u,v,w;
	
	bool operator<(const Edge& other) const{
	    return w<other.w;  
		  }
};

class UnionFind{
	private:
		vector<int> parent,rank;
	public:
		UnionFind(int n){
			parent.resize(n+1);
			rank.resize(n+1,0);
			for (int i=1;i<=n;i++){
				parent[i]=i;
			}
		}
	
	int find(int x){
		if(parent[x]!=x){
			parent[x]=find(parent[x]);
		}
		return parent[x];
	}
	
	int unite(int x,int y){
		int rx=find(x);
		int ry=find(y);
		if (rx==ry){
			return false;
		}
		if (rank[rx]<rank[ry]){
			parent[rx]= ry;
		}else if(rank[rx] >rank[ry]){
			parent[ry]=rx;
		}else{
			parent[ry] =rx;
			rank[rx] ++;
			
		}
		return true;
	}
};
int main(){
		ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        int n,m;
        cin>>n>>m;
        vector<Edge> edges(m);
        
        for (int i=0;i<m;i++){
        	cin>>edges[i].u>>edges[i].v>>edges[i].w;
		}
		sort(edges.begin(),edges.end());
		UnionFind uf(n);
		int edgesused=0;
		long long totalWeight=0;
		for (const auto& edge : edges){
			if(uf.unite(edge.u,edge.v)){
				totalWeight += edge.w;
				edgesused++;
			    if (edgesused==n-1){
			    	break;
				}	
			}
			
		}
		if (edgesused==n-1){
			cout<<totalWeight<<endl;
		}else {
			cout<<"orz"<<endl;
		}
		return 0;
	}	

	
	

