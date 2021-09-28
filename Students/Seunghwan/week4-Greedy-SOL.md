# 4주차 그리디 문제풀이
- PPAP
- 그렇고 그런 사이
## 1. PPAP
https://www.acmicpc.net/problem/16120
### 접근방법
이번 문제는 Greedy 알고리즘을 통해 해결하였다. PPAP 문자열에서 P 하나를 PPAP로 바꾼 문자열이 PPAP가 된다는 정의에서 이해가 조금 필요했다.

이 정의를 간단한 예시들로 정리해보면 PPAP -> PPAPPAP(1번 P가 PPAP가 된 경우), PPPAPAP(2번 P가 PPAP가 된 경우), PPAPPAP(3번 P가 PPAP가 된 경우)로 변할 수 있고, 이 문자열 모두 PPAP에 해당한다는 것이다.

규칙을 찾는데 시간이 조금 걸렸다.

- A가 반드시 있어야 한다.
- 앞에서부터 P가 2개 이상 존재한 뒤에 A가 있어야 한다.
- A는 2번 연속으로 나올 수 없다.
규칙을 바탕으로 다음과 같이 해결하였다.

- 문자열이 P라면 st벡터에 P를 넣고 true를 반환하도록 한다.
- 문자열 길이만큼 검사를 진행한다.
- 문자열의 현재 인덱스에 해당하는 문자가 P일 경우, st벡터에 push_back('P') 해준다.
- 문자열의 현재 인덱스가 P가 아니고, st에 들어간 P가 2개 이상이고, 다음 인덱스에 해당하는 문자가 P일 때, st벡터에서 P 2개를 pop_back() 해준다.
- 이 외의 경우에는 false를 반환한다.
- 문자열 길이만큼 무사히 검사를 마치면 true를 반환한다.
xcode에서는 잘 실행됐지만 백준에 제출을 하니 70%대에서 오답처리 되었다. 반례를 생각하다가 PPPP는 PPAP가 아니라는 것을 생각하게 되었다. 본인이 작성한 코드에서는 PPPP도 true로 반환되기 때문에 오답처리된 것이었다.

- PPPP를 NP로 출력시키기 위해 Solution함수 마지막에 st에 들어간 P의 길이를 확인하여 P가 1개라면 true를, 1개가 아니라면 false를 반환하도록 하였다.
PPAP -> st:+P, +P, -P, -P, +P st.size()=1
PPPAPAP -> st:+P, +P, +P, -P, -P, +P, -P, -P, +P st.size()=1
PPPP -> st: +P, +P, +P, +P st.size()=4

### 구현
```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string ppap;
vector<int> st;

void Input(){
    cin>>ppap;
}

bool Solution(){
    if(ppap.size()==1&&ppap.front()=='P'){
        st.push_back('P');
    }
    else{
        for(int i=0; i<ppap.size(); i++){
            if(ppap[i]=='P'){
                st.push_back('P');
            }
            else if(st.size()>=2&&ppap[i+1]=='P'){
                st.pop_back();
                st.pop_back();
            }
            else{
                return false;
            }
        }
    }
    if(st.size()==1)
        return true;
    else
        return false;
}

void Solve(){
    if(Solution())
        cout<<"PPAP"<<endl;
    else
        cout<<"NP"<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solve();
    return 0;
}
```

## 2. 그렇고 그런 사이
https://www.acmicpc.net/problem/20921
### 접근방법
이번 문제는 Greedy 알고리즘을 활용하여 해결하였다. 우선 규칙을 찾아보는 것이 중요했다.

- vi가 가질 수 있는 그렇고 그런 사이는 n-i개이다.
- 이를 0부터 n-1까지 반복하고 더하여 k를 만들어내는 문제이다.
- k의 범위가 0보다 크거나 같고, n-1보다 작거나 같다면 k+1의 값하나만 앞으로 가져오면 해결된다.
- k가 n과 2n-1사이라면 n-1과 남은 수 중 하나의 위치를 앞으로 옮기면 된다.
- k가 2n-2와 3n-6사이라면 n-1, n-2와 남은 수 중 하나의 위치를 옮기면 된다.
- k의 범위에 따라 계속해서 선택되는 수들을 늘리면 k의 n(n-1)/2까지의 경우를 모두 만들 수 있다.
- 즉, k를 n-1부터 비교하며 k가 이 수보다 크다면 k에 이 수를 빼주는 것을 반복한다.
- n-i가 필요하면 n-i+1을 배열의 제일 왼쪽부터 차례대로 채워 나가고 이 작업이 끝나면 남은 수를 오름차순으로 비어있는 곳에 배치해준다.
- visited배열은 수를 사용한 것을 체크한다.

### 구현
```c++
#include <iostream>
#include <cstring>
#define MAX 4243
using namespace std;

int n, k;
int v[MAX];
bool visited[MAX];

void Input(){
    cin>>n>>k;
    memset(v, 0, sizeof(v));
    memset(visited, false, sizeof(visited));
}

void Solution(){
    int end=n;
    int idx=1;
    while(k){
        if(k>=end-1){
            k-=(end-1);
            v[idx]=end;
            idx++;
            visited[end]=true;
        }
        end--;
    }
    int num=1;
    for(int i=1; i<=n; i++){
        if(v[i]!=0) continue;
        while(visited[num])
            num++;
        v[i]=num++;
    }
}

void Solve(){
    for(int i=1; i<=n; i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solution();
    Solve();
    return 0;
}
```
