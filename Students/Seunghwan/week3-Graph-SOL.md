# 3주차 그래프 문제풀이
- MooTube (Silver)
- 전단지 돌리기
- 색칠하기 (fail)

## 1. MooTube (Silver)
https://www.acmicpc.net/problem/15591

### 접근방법
이번 문제는 BFS를 통한 그래프 탐색으로 해결하였다. 문제를 이해하는데 조금 오래 걸렸던 것 같다.

- 매 사이클마다 방문한 영상인지 체크하기 위한 visited 배열을 선언한다.
- 영상은 vector 배열로 선언하여 각 영상에서 추천되는 영상을 저장한다.
- 영상 간의 연결은 양방향이므로 양방향으로 저장해준다.
- 영상 v와 연결된 영상들과 그에 해당하는 k 값을 확인한기 위해 BFS 방식을 활용한다.
- visited가 false인 영상들 중에서 curcost가 k보다 크거나 같은 영상이 있다면 visited를 true로 저장해주고 cnt를 증가시킨다. 이는 추천되는 영상이므로 결과값을 증가시키는 과정이다.
정리하면, 영상 v와 연결된 모든 영상들과의 r값을 확인하고 해당 next의 r값이 k값보다 크거나 같으면 cnt를 증가시킨다. 중복 확인을 방지하기 위해 visited배열을 사용하고, next를 queue에 넣어 next에 대한 위 과정을 반복한다. (queue가 비어있을 때까지 반복하므로 영상 vector의 끝까지 확인하는 셈이다.)

### 구현
```c++
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define MAX 5001
using namespace std;

int n, q;
vector<pair<int, int>> video[MAX];
int k, v;
bool visited[MAX]={false, };

void Input(){
    cin>>n>>q;
    for(int i=0; i<n-1; i++){
        int a,b,c;
        cin>>a>>b>>c;
        video[a].push_back({b,c});
        video[b].push_back({a,c});
    }
}

void InputQ(){
    cin>>k>>v;
}

void BFS(int cost, int cur){
    memset(visited, false, sizeof(visited));
    queue<int> Q;
    int cnt=0;
    visited[cur]=true;
    Q.push(cur);
    while(!Q.empty()){
        int now=Q.front();
        Q.pop();
        for(int i=0; i<video[now].size(); i++){
            int next=video[now][i].first;
            int curcost=video[now][i].second;
            if(visited[next])
                continue;
            if(curcost>=k){
                cnt++;
                visited[next]=true;
                Q.push(next);
            }
        }
    }
    cout<<cnt<<endl;
}

void Solution(){
    Input();
    for(int i=0; i<q; i++){
        InputQ();
        BFS(k, v);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Solution();
    return 0;
}
```

## 2. 전단지 돌리기
https://www.acmicpc.net/problem/19542

### 접근방법
이번 문제는 DFS를 통한 그래프 탐색으로 해결하였다. 결과적으로 현재 위치에서 갈 수 있는 최대 깊이-현재 위치의 깊이>=d인 위치까지 가면 모든 노드에 전단지를 돌릴 수 있게된다.

- 경로들을 vector배열로 저장해준다.
- 각 노드에서의 깊이와 최대 깊이를 나타내기 위한 depth와 maxDepth를 선언한다.
- 경로는 양방향이므로 양방향으로 저장해준다.
- DFS함수를 통해 그래프 탐색을 한다. 이때 내부에서 다음 노드의 깊이를 정의해주고, 재귀호출한다. 이 과정에서 최대 깊이가 구해진다.
- 최대깊이-현재깊이가 d보다 크거나 같다면 cnt에 2를 더해준다. 2를 더하는 이유는 경로를 다시 돌아와야 하기 때문이다.
- cnt가 2보다 크거나 같다면 cnt-2를 출력해주고, 작다면 0을 출력해준다. 이는 s가 최소 1이기 때문이다. (1이 아닌 2인 이유는 왕복을 고려해야 하기 때문이다.)
이 코드를 처음에 실행하였을 때,
```c++
maxDepth=depth=vector<int>(n+1, 0);
depth[s]=1;
```
이 부분에서 
```c++
maxDepth=depth=vector<int>(n+1, 0);
```
를 작성하지 않아 에러가 발생하였다. depth[s]가 bad access라는 내용이었다. 곰곰히 생각해보니, vector는 queue나 stack처럼 차곡차곡 쌓는 구조인데 depth에 대한 값들이 하나도 들어가 있지 않은 상태에서 s라는 인덱스를 요구했기 때문이었다. vector를 사용하는데 주의해야 할 부분이라고 생각했다.

### 구현
```c++
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 100001
using namespace std;

int n,s,d;
vector<int> road[MAX];
vector<int> depth;
vector<int> maxDepth;
int cnt=0;

void Input(){
    cin>>n>>s>>d;
    for(int i=0; i<n-1; i++){
        int a,b;
        cin>>a>>b;
        road[a].push_back(b);
        road[b].push_back(a);
    }
}

int DFS(int cur){
    int result=depth[cur];
    for(int i=0; i<road[cur].size(); i++){
        int des=road[cur][i];
        if(!depth[des]){
            depth[des]=depth[cur]+1;
            result=max(result, DFS(des));
        }
    }
    maxDepth[cur]=result;
    if(maxDepth[cur]-depth[cur]>=d){
        cnt+=2;
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    maxDepth=depth=vector<int>(n+1, 0);
    depth[s]=1;
    DFS(s);
    if(cnt-2>=0)
        cout<<cnt-2<<endl;
    else
        cout<<0<<endl;
    return 0;
}
```
## 3. 색칠하기 (fail)
https://www.acmicpc.net/problem/13265

### 접근방법
이번 문제는 DFS를 통해 해결하려 했지만 결국은 해결하지 못하였다. 

- 각 동그라미에 대한 색을 color배열로 정의한다.
- chk이중배열로 간선을 정의한다.
- DFS를 통하여 인접한 동그라미의 색을 정하고, 만약 이미 동그라미의 색이 정해져있다면 색을 검사한다. 이 때 색이 2보다 크거나, 현재 동그라미의 색과 같다면 결과를 저장하는 result는 false가 된다.
- DFS를 실행하기 전에, 고립된 동그라미가 있는지 확인하기 위한 과정을 거친다. 간선이 없다면 out이 true가 되어 다음 동그라미로 넘어가고, 간선이 있어 out이 false가 되면 DFS를 통하여 검사를 진행한다.
- 결과를 저장하는 result가 true이면 2가지 색으로 칠하는 것이 가능하므로 possible을, false라면 impossible을 출력해준다.

xcode에서는 잘 구동되지만 백준에 제출하면 91%에서 오답처리된다. 틀린 부분을 찾아보았지만 찾지 못하였다... 

### 구현
```c++
#include <iostream>
#include <algorithm>
#define MAX 1001
using namespace std;

int t;
int n, m;
int color[100001]={0, };
bool chk[MAX][MAX]={false, };
bool result=true;

void Input(){
    cin>>n>>m;
    for(int i=0; i<m; i++){
        int x,y;
        cin>>x>>y;
        chk[x][y]=true;
        chk[y][x]=true;
    }
}

void DFS(int idx, int cnt){
    if(!result)
        return;
    if(cnt==n)
        return;
    if(color[idx]==1){
        for(int i=1; i<=n; i++){
            if(chk[idx][i]){
                if(color[i]==1)
                    result=false;
                else if(color[i]==0)
                    color[i]=2;
                else
                    continue;
                DFS(i, cnt+1);
            }
        }
    }
    else if(color[idx]==2){
        for(int i=1; i<=n; i++){
            if(chk[idx][i]){
                if(color[i]==2)
                    result=false;
                else if(color[i]==0)
                    color[i]=1;
                else
                    continue;
                DFS(i, cnt+1);
            }
        }
    }
}

void Init(){
    for (int i=0; i<=m; i++){
        color[i]=0;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            chk[i][j]=false;
        }
    }
    result=true;
}


void Solution(){
    cin>>t;
    for(int i=0; i<t; i++){
        if (i!=0)
            Init();
        Input();
        for(int i=1; i<=n; i++){
            bool out=true;
            for(int j=1; j<=n; j++){
                if(chk[i][j]){
                    out=false;
                    break;
                }
            }
            if(!out){
                color[i]=1;
                DFS(1, 0);
                break;
            }
        }
        if(result)
            cout<<"possible"<<endl;
        else
            cout<<"impossible"<<endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Solution();
    return 0;
}
```
