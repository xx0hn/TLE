#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool check(int n, int m, int nx, int ny);
int BFS(int sx, int sy, int ex, int ey,vector<vector<bool>>& vistied, int n, int m)
{
    int dir[][2]={
        1,0,
        -1,0,
        0,1,
        0,-1
    };
    int ret(0); //전선의 수
    bool flag=false;
    vector<vector<bool>> tempVisited(vistied);
    //탐색전 전선상태를 저장
    vector<vector<pair<int, int>>> trace(n+1,vector<pair<int ,int>>(m+1,{-1,-1}));
    //전선 역추적
    queue<pair<int ,int>> q;
    q.push({sx,sy});
    trace[sy][sx]={-1,-1};
    tempVisited[ey][ex]=false;  //최종지점 방문을 위해서 false로 설정
    while(!q.empty())
    {
        auto point=q.front();q.pop();
        if(point.first==ex&&point.second==ey)
        {
            flag=true;
            break;
        }
        for(int i=0;i<4;++i)
        {
            int nx=point.first+dir[i][0];
            int ny=point.second+dir[i][1];
            if(!check(n,m,nx,ny))continue;
            if(tempVisited[ny][nx])continue;
            trace[ny][nx]=point;
            tempVisited[ny][nx]=true;
            q.push({nx,ny});
        }
    }
    if(!flag)
    {
        //도달 실패
        return -1;
    }
    else
    {
        //역추적하며 전선 배치
        pair<int, int> point={ex,ey};
        pair<int ,int> end={-1,-1};
        while(trace[point.second][point.first]!=end)
        {
            vistied[point.second][point.first]=true;
            ++ret;point=trace[point.second][point.first];
        }
        return ret;
    }
}

int main()
{
	int ans=INT32_MAX;
	int len_a,len_b;
	int n,m;
	int sx_a,sy_a,ex_a,ey_a,
		sx_b,sy_b,ex_b,ey_b;
	vector<vector<bool>> visited;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	visited.resize(n+1,vector<bool>(m+1,false));
	cin>>sy_a>>sx_a>>ey_a>>ex_a;
	cin>>sy_b>>sx_b>>ey_b>>ex_b;
	visited[sy_a][sx_a]=visited[ey_a][ex_a]=visited[sy_b][sx_b]=visited[ey_b][ex_b]=true;
	len_a=BFS(sx_a,sy_a,ex_a,ey_a,visited,n,m);
	len_b=BFS(sx_b,sy_b,ex_b,ey_b,visited,n,m);
	if(len_a!=-1&&len_b!=-1)
	{
		ans=len_a+len_b;
	}
	for(int i=0;i<=n;++i)
	{
		for(int j=0;j<=m;++j)
		{
			visited[i][j]=false;
		}
	}
	visited[sy_a][sx_a]=visited[ey_a][ex_a]=visited[sy_b][sx_b]=visited[ey_b][ex_b]=true;
	len_b=BFS(sx_b,sy_b,ex_b,ey_b,visited,n,m);
	len_a=BFS(sx_a,sy_a,ex_a,ey_a,visited,n,m);
	if(len_a!=-1&&len_b!=-1)
	{
		ans=min(ans,len_a+len_b);
	}
	if(ans==INT32_MAX)
	{
		cout<<"IMPOSSIBLE";
	}
	else
	{
		cout<<ans;
	}
	return 0;
}

bool check(int n, int m, int nx, int ny)
{
	return ny<=n&&ny>=0&&nx<=m&&nx>=0;
}