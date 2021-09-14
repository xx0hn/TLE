# 2주차 백트레킹 문제풀이
- N과 M (11)
- 연산자 끼워넣기 (2)
- 감소하는 수

## 1. N과 M (11)
https://www.acmicpc.net/problem/15665

### 접근방법
이번 문제는 백트레킹 알고리즘을 활용하여 해결하였다. 문제의 조건없이 출력하는 것은 쉽지만 같은 수를 여러 번 골라도 되지만 길이M의 수열끼리는 중복을 허용하지 않는다는 조건에서 생각이 필요했다.

- bool형 num_chk 배열을 통해 입력된 값이 존재하는지 확인한다.
- 만약 입력된 값이 존재한다면 arr 벡터에 넣지 않고, 존재하지 않을 때만 벡터에 push_back해준다. 이는 수열의 중복을 제거하는 역할을 한다.
- arr을 오름차순으로 정렬해준다. 이는 결과 출력이 오름차순으로 형성되기 위함이다.
- 같은 수를 여러 번 골라도 되기 때문에 DFS 함수 내에서는 따로 조건을 넣어주지 않는다.
- 변수 cnt로 result 배열의 인덱스(DFS의 깊이)를 나타내므로 result에 값을 넣을 때마다 cnt값을 증가시킨다.
- 만약 cnt가 m과 크기가 같아지면 result배열을 출력한다.

처음에는 DFS 안에서 중복을 제거하려다가 시간초과가 발생하였고, 이를 입력 과정에서 제거하는 방식으로 변경하여 시간을 단축시켰다.
### 구현
```c++
#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 8
using namespace std;

int n, m, a;
vector<int> arr;
int result[MAX];
bool num_chk[10001];

void Input(){
    cin>>n>>m;
    for(int i=0; i<n; i++){
        cin>>a;
        if(!num_chk[a]){
            arr.push_back(a);
            num_chk[a]=true;
        }
    }
    sort(arr.begin(), arr.end());
}

void DFS(int cnt){
    if(cnt==m){
        for(int i=0; i<m; i++){
            cout<<result[i]<<" ";
        }
        cout<<"\n";
        return;
    }
    for(int i=0; i<arr.size(); i++){
        result[cnt]=arr[i];
        DFS(cnt+1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    DFS(0);
    return 0;
}
```

## 2. 연산자 끼워넣기 (2)
https://www.acmicpc.net/problem/15658

### 접근방법 (C++)
이번 문제는 백트레킹을 통해 해결하였다.

- DFS의 인자를 현재 인덱스+1,누적된 결과값, +갯수, -갯수, *갯수, /갯수로 정의한다.
- 모든 경우를 전부 비교해야 하므로 각 연산자의 갯수가 0보다 크다면 그 연산을 진행한다.
- DFS의 첫번째 인자, 즉 현재 인덱스+1에 해당하는 값이 n과 같아지면 하나의 식을 완성한 것이므로 대소비교를 통해 maxi, mini를 업데이트 시켜준다.
처음에는 DFS의 인자를 현재 인덱스+1,누적된 결과값로만 넣고 진행하였는데, 이렇게 구현하게 되면 연산자들에 대한 모든 경우를 구할 수 없었다. 그래서 연산자의 수를 직접 변경하는 것이 아닌, DFS함수 내에서만 임의 변경하여 모든 경우를 탐색할 수 있게 하였다.

그리고 maxi와 mini의 초기값을 설정할 때, result가 음수인 경우를 생각하지 못하고, mini는 10억으로 설정하였지만, maxi를 0으로 설정하여 오답처리 되었다. 이를 maxi=-10억, mini=10억하여 해결하였다.

### 구현 (C++)
```c++
#include <iostream>
#include <algorithm>
#define MAX 12
using namespace std;

int n;
long long arr[MAX];
int op[4];
long long maxi=-1000000000;
long long mini=1000000000;

void Input(){
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    for(int i=0; i<4; i++){
        cin>>op[i];
    }
}

void DFS(int cur, long long result, int plus, int minus, int mul, int div){
    if(cur==n){
        if(maxi<result)
            maxi=result;
        if(mini>result)
            mini=result;
        return;
    }
    if(plus>0){
        DFS(cur+1, result+arr[cur], plus-1, minus, mul, div);
    }
    if(minus>0){
        DFS(cur+1, result-arr[cur], plus, minus-1, mul, div);
    }
    if(mul>0){
        DFS(cur+1, result*arr[cur], plus, minus, mul-1, div);
    }
    if(div>0){
        if(result==0)
            DFS(cur+1, 0, plus, minus, mul, div-1);
        else
            DFS(cur+1, result/arr[cur], plus, minus, mul, div-1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    DFS(1, arr[0], op[0], op[1], op[2], op[3]);
    cout<<maxi<<endl<<mini<<endl;
    return 0;
}
```

### 접근방법 (Python)
파이썬으로도 해결해보았다. C++ 코드와 조금은 다르게 풀어보았다.

- DFS의 인자를 줄이는 대신에 DFS 재귀호출 이후 갯수를 줄였던 연산자의 갯수를 다시 늘린다.
- maxi, mini의 값은 python 내장함수인 max, min을 사용하여 구하였다.
나누기 부분에서 계속해서 오답처리가 되었고, result//arr[cur]을 int(result/arr[cur])로 변경하자 해결되었다. 문제의 나눗셈이 C++14 기준을 따라서 그런 것 같다.

### 구현 (Python)
```python
n=int(input())
arr=list(map(int, input().split()))
op=list(map(int, input().split()))
maxi=-1000000000
mini=1000000000
def DFS(cur, result):
    global maxi
    global mini
    if cur==n:
        maxi=max(maxi, result)
        mini=min(mini, result)
        return
    if op[0]>0:
        op[0]-=1
        DFS(cur+1, result+arr[cur])
        op[0]+=1
    if op[1]>0:
        op[1]-=1
        DFS(cur+1, result-arr[cur])
        op[1]+=1
    if op[2]>0:
        op[2]-=1
        DFS(cur+1, result*arr[cur])
        op[2]+=1
    if op[3]>0:
        op[3]-=1
        if result==0:
            DFS(cur+1, 0)
            op[3]+=1
        else:
            DFS(cur+1, int(result/arr[cur]))
            op[3]+=1
DFS(1, arr[0])
print(maxi)
print(mini)
```

## 3. 감소하는 수
https://www.acmicpc.net/problem/1038

### 접근방법 (C++)
이번 문제는 백트레킹을 활용하는 문제였다. 처음에 고민했던 것은 결과값을 n을 입력 받은 후에 구할지, 미리 결과값을 배열로 저장해둘지 결정하는 것이었다. 본인은 결과값들을 배열에 저장하기로 하였다.

우선 조건으로 명시되어야 하는 것이 앞의 자리가 가장 커야한다는 것이었고, 그 다음 자리 수들은 각자의 앞의 자리보다 작아야한다는 것이었다. 이 값들을 검증하고 넣기 위해 result를 vector로 만들었다.

- DFS함수의 인자로 idx, cnt를 둔다. idx는 result vector에 들어가게 될 값이 되고, cnt는 한번의 사이클동안 result vector에 들어가는 수들을 세는 값이 된다.
- DFS함수 안에서 cnt가 10보다 커지면 return을 해준다. 이는 result vector에 9,876,543,210이 들어갈 때만 해당된다.
- i를 0부터 9까지의 범위로 for문을 돌리며 idx%10이 i보다 큰 경우에만 idx*10+i, cnt+1의 인자가 들어간 DFS함수를 재귀 호출 해준다.
- for문이 끝까지 돌아가고 난 뒤에 return을 해준다.
- 이 DFS함수의 idx를 0부터 9까지 넣고 반복하면 result vector가 완성된다.
- 완성된 result vector는 순서가 뒤죽박죽이므로 sort함수를 사용해 오름차순 정렬해준다.
- 입력된 n이 result vector의 크기보다 크다면 이는 범위를 벗어나므로 -1을 출력해준다.
- 그 외의 경우에는 result[n]을 출력해준다.

### 구현 (C++)
```c++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<long long> result;

void Input(){
    cin>>n;
}

void DFS(long long idx, int cnt){
    if(cnt>10)
        return;
    result.push_back(idx);
    for(int i=0; i<10; i++){
        if(idx%10>i){
            DFS(idx*10+i, cnt+1);
        }
    }
    return;
}

void Solution(){
    for(int i=0; i<10; i++){
        DFS(i, 1);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solution();
    sort(result.begin(), result.end());
    if(result.size()<=n){
        cout<<"-1"<<endl;
    }
    else if(result.size()>n) {
        cout<<result[n]<<endl;
    }
    return 0;
}
```

### 접근방법 (Python)
C++로 풀어봤던 문제를 python으로 다시 풀어보았다. 확실히 python은 내장함수가 많아서 코드가 짧게 나오는 것 같다. append와 len, sorted 등을 사용하였다.

### 구현 (Python)
```python
n=int(input())
result=[]
def DFS(idx, cnt):
    if cnt>10:
        return
    result.append(idx)
    for i in range(10):
        if idx%10>i:
            DFS(idx*10+i, cnt+1)
    return
for i in range(10):
    DFS(i, 1)
result=sorted(result)
if len(result)<=n:
    print("-1")
else:
    print(result[n])
```
