#include <iostream>
#include <vector>
using namespace std;

void DFS(int now, int previous, vector<vector<int>>& tree, vector<int>& depth,vector<vector<int>>& parent_dp);
void Connect(int u, int v, vector<vector<int>>& tree);
int Find_LCA(int u, int v, vector<vector<int>>& tree, vector<int>& depth,vector<vector<int>>& parent_dp);
int main()
{
    int n;
    int max_i(0);
    vector<int> depth;
    vector<vector<int>> tree, parent_dp;
    n=10;
    while((1<<max_i)<n)++max_i;
    tree.resize(n+1);
    depth.resize(n+1);
    parent_dp.resize(max_i+1,vector<int>(n+1));
    Connect(3,6,tree);
    Connect(4,5,tree);
    Connect(2,3,tree);
    Connect(2,4,tree);
    Connect(1,2,tree);
    Connect(3,7,tree);
    Connect(6,10,tree);
    Connect(7,8,tree);
    Connect(2,9,tree);
    DFS(1,1,tree,depth,parent_dp);
    for(int i=1;i<=max_i;++i)
    {
        for(int v=1;v<=n;++v)
        {
            parent_dp[i][v]=parent_dp[i-1][parent_dp[i-1][v]];
        }
    }
    cout<<"LCA(3,5): "<<Find_LCA(3,5,tree,depth,parent_dp)<<"\n";
    cout<<"LCA(6,10): "<<Find_LCA(6,10,tree,depth,parent_dp)<<"\n";
    cout<<"LCA(5,9): "<<Find_LCA(5,9,tree,depth,parent_dp)<<"\n";
    cout<<"LCA(6,8): "<<Find_LCA(6,8,tree,depth,parent_dp)<<"\n";
}

void DFS(int now, int previous, vector<vector<int>>& tree, vector<int>& depth,vector<vector<int>>& parent_dp)
{
    parent_dp[0][now]=previous;
    depth[now]=depth[previous]+1;
    for(int i=0;i<tree[now].size();++i)
    {
        if(tree[now][i]==previous)continue;
        DFS(tree[now][i], now,tree,depth,parent_dp);
    }
}

void Connect(int u, int v, vector<vector<int>>& tree)
{
    tree[u].push_back(v);
    tree[v].push_back(u);
}
int Find_LCA(int u, int v, vector<vector<int>>& tree, vector<int>& depth,vector<vector<int>>& parent_dp)
{
    if(depth[u]<depth[v])
    {
        swap(u,v);
    }
    int distance=depth[u]-depth[v];
    for(int i=0;distance;++i)
    {
        if(distance&1)
        {
            u=parent_dp[i][u];
        }
        distance>>=1;
    }
    if(u==v)
    {
        return u;
    }
    for(int i=parent_dp.size()-1;i>=0;--i)
    {
        if(parent_dp[i][u]!=parent_dp[i][v])
        {
            u=parent_dp[i][u];
            v=parent_dp[i][v];
        }
    }
    return parent_dp[0][u];
}