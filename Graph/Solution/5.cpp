#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/********
BFS 사용
*********/
int main()
{
	int t;
	int n,m;
	vector<int> colors;
	queue<pair<int ,int>> q;
	vector<vector<int>> graph;
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--)
	{
		bool flag=true; //2가지색으로 칠 할 수 있는 지 확인
		cin>>n>>m;
        //그래프 초기화
		for(int i=0;i<graph.size();++i)
		{
			graph[i].clear();
		}
		graph.clear();
		graph.resize(n+1);
		for(int i=0;i<m;++i)
		{
			int a,b;
			cin>>a>>b;
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		colors.clear();
		colors.resize(n+1);
		for(int i=1;i<=n;++i)
		{
			colors[i]=0;    //아무것도 안 칠한 상태로 초기화
		}
		for(int i=1;i<=n&&flag;++i)
		{
			if(colors[i])continue;
            colors[i]=1;    
			q.push({i,1});  //시작 정점과 해당 정점의 색깔을 큐에 삽입
			while(!q.empty()&&flag)
			{
				int vertex=q.front().first; //현재 정점
				int next_color=q.front().second;    //색깔
				q.pop();
				next_color=3-next_color; 
                //현재 색이 1이면 다음색은 2
                //현재 색이 2이면 다음색은 1
				for(int next:graph[vertex])
				{
					if(colors[next]==0)
					{
                        //색깔이 안칠해졌다면
                        //칠하고 큐에 삽입
						colors[next]=next_color;
						q.push({next,next_color});
					}
					else if(colors[next]!=next_color)
					{
                        //다른 색을 칠해야 한다면 불가능한 경우
						flag=false;
						break;
					}
				}
			}
            //큐를 비워줌
			while(!q.empty())q.pop();
		}
		if(flag)
		{
			cout<<"possible\n";
		}
		else
		{
			cout<<"impossible\n";
		}
	}
	return 0;
}