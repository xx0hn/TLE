#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int previous, int now, vector<vector<int>>& graph, vector<int>& depth_vec,int d);
int dfs(int previous, int now, vector<vector<int>>& graph, vector<int>& depth_vec);

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<vector<int>> graph;
    vector<int> depth_vec;
    int n,s,d;
    cin>>n>>s>>d;
    graph.resize(n+1);
    depth_vec.resize(n+1);
    for(int i=1;i<n;++i)
    {
        int x,y;
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(0,s,graph,depth_vec);
    cout<<solve(0,s,graph,depth_vec,d)*2;
    return 0;
}

int dfs(int previous, int now, vector<vector<int>>& graph, vector<int>& depth_vec)
{
    //가장 깊은 정점까지의 거리를 구함
    int& ref=depth_vec[now];
    for(auto& next:graph[now])
    {
        if(next==previous)continue;
        ref=max(ref,dfs(now,next,graph,depth_vec)+1);
    }
    return ref;
}

int solve(int previous, int now, vector<vector<int>>& graph, vector<int>& depth_vec,int d)
{
    //now 에서 리프노드와 거리가 D이상인 정점들까지 가는 간선의 수
    int ret=0;
    for(auto& next:graph[now])
    {
        if(next==previous)continue;
        if(depth_vec[next]>=d)
        {
            ret+=solve(now, next,graph, depth_vec,d)+1;
        }
    }
    return ret;
}