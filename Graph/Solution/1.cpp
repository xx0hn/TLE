#include <iostream>
#include <vector>
using namespace std;

/*
DFS 사용 (BFS로도 풀 수 있음)
*/
int dfs(vector<vector<pair<int, int>>>& graph, int prev,int now, int k)
{
    int ret=0;
    for(auto iter=begin(graph[now]);iter!=end(graph[now]);++iter)
    {
        if(iter->first==prev)
        {
            continue;
        }
        if(iter->second>=k)
        {
            ret+=(1+dfs(graph, now, iter->first, k));
        }
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<vector<pair<int ,int>>> graph;
    int n,Q;
    cin>>n>>Q;
    graph.resize(n+1);
    for(int i=1;i<n;++i)
    {
        int p,q,r;
        cin>>p>>q>>r;
        graph[p].push_back({q,r});
        graph[q].push_back({p,r});
    }
    while(Q--)
    {
        int k,v;
        cin>>k>>v;
        cout<<dfs(graph,v,v,k)<<"\n";
    }
    return 0;
}
