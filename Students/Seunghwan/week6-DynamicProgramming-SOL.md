# 6주차 다이나믹프로그래밍 문제풀이
- 내려가기
- 동전 1
- 연속합 2
## 1. 내려가기
https://www.acmicpc.net/problem/2096
### 접근방법
이번 문제는 다이나믹 프로그래밍을 통해 해결하였다. 처음에는 주어진 2차원 배열을 만든 뒤에 내려가며 최대와 최소에 해당하는 수들을 각각 저장하여 해결해야겠다고 생각을 했다. 하지만 그렇게 되면 입력값이 너무 많아져 메모리 제한을 초과한다는 사실을 알게 되었다. 그래서 각 줄을 입력 받을 때 마다 누적값의 최대와 최소를 구하여 저장해놓는 방식으로 구현하였다.

- n을 입력받는다.
- 각 줄에 해당하는 가장 큰 결과 값과 가장 작은 결과값을 저장할 maxDP, minDP 배열을 선언한다.
- maxDP, minDP를 구하기 위해 계산값을 임시로 저장해 놓을 maxTemp, minTemp 배열을 선언한다.
- 0부터 n-1까지 반복하는 i에 대한 for문을 돌린다.
- num1,num2,num3을 입력받는다. 이는 입력되는 2차원 배열의 한 줄을 의미하는 것이다.
- 0부터 2까지 반복하는 j에 대한 for문을 돌린다.
-> j가 0일때는 num1을, 1일때는 num2를, 2일때는 num3을 선택한 상황으로 이는 왼쪽, 가운데, 오른쪽 수를 의미한다.
-> j에 해당하는 num과 이전의 maxDP, minDP를 이용하여 j에 해당하는 maxTemp, minTemp를 구한다.
- 0부터 2까지 반복하는 j에 대한 for문을 돌린다.
-> maxTemp, minTemp의 값을 maxDP, minDP에 저장한다.
- 반복문이 모두 끝나면 maxDP의 최댓값과 minDP의 최솟값을 출력한다.

### 구현
- Python
```python
n=int(input())
maxDP=[0]*3
minDP=[0]*3
maxTemp=[0]*3
minTemp=[0]*3
for i in range(n):
    num1,num2,num3 = map(int, input().split())
    for j in range(3):
        if j==0:
            maxTemp[j]=num1+max(maxDP[j], maxDP[j+1])
            minTemp[j]=num1+min(minDP[j], minDP[j+1])
        elif j==1:
            maxTemp[j]=num2+max(maxDP[j-1], maxDP[j], maxDP[j+1])
            minTemp[j]=num2+min(minDP[j-1], minDP[j], minDP[j+1])
        else:
            maxTemp[j]=num3+max(maxDP[j-1], maxDP[j])
            minTemp[j]=num3+min(minDP[j-1], minDP[j])
    for j in range(3):
        maxDP[j]=maxTemp[j]
        minDP[j]=minTemp[j]
print(max(maxDP), min(minDP))
```
- C++
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int maxDP[3], minDP[3], maxTemp[3], minTemp[3];

void Input(){
    cin>>n;
}

void Solution(){
    int num1, num2, num3;
    int maxi=0, mini=9999999;
    for(int i=0; i<n; i++){
        cin>>num1>>num2>>num3;
        for(int j=0; j<3; j++){
            if(j==0){
                maxTemp[j]=num1+max(maxDP[j], maxDP[j+1]);
                minTemp[j]=num1+min(minDP[j], minDP[j+1]);
            }
            if(j==1){
                maxTemp[j]=num2+max(maxDP[j-1], max(maxDP[j], maxDP[j+1]));
                minTemp[j]=num2+min(minDP[j-1], min(minDP[j], minDP[j+1]));
            }
            if(j==2){
                maxTemp[j]=num3+max(maxDP[j-1], maxDP[j]);
                minTemp[j]=num3+min(minDP[j-1], minDP[j]);
            }
        }
        for(int j=0; j<3; j++){
            maxDP[j]=maxTemp[j];
            minDP[j]=minTemp[j];
        }
    }
    for(int i=0; i<3; i++){
        if(maxDP[i]>maxi){
            maxi=maxDP[i];
        }
        if(minDP[i]<mini){
            mini=minDP[i];
        }
    }
    cout<<maxi<<" "<<mini<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solution();
    return 0;
}
```
## 2. 동전 1
https://www.acmicpc.net/problem/2293
### 접근방법
이번 문제는 다이나믹 프로그래밍으로 해결하는 문제였다. 반복되는 연산을 저장하여 연산 횟수를 줄이는 다이나믹 프로그래밍의 장점을 이용했다.

- n, k 를 입력받는다.
- 동전의 금액을 입력받는 coin 배열을 선언하고 입력받는다.
- 동전의 합의 경우 수를 저장하는 answer 배열을 선언한다. 이때 answer 배열의 인덱스는 동전의 합을 의미한다. answer배열의 크기는 k+1이 된다.
-> ex) answer[4]는 동전의 합이 4가 되는 경우의 수를 저장하는 원소이다.
- answer[0]은 1로 저장한다. 이는 answer[가장 작은 동전 금액]을 구하기 위함이다.
- 이중 for문을 통하여 값을 구한다.
-> 바깥 for문은 i가 coin배열을 돌게 한다.
-> 안쪽 for문은 j가 coin배열의 해당 원소부터 k까지 돌게 한다.
-> 안쪽 for문에서 조건문을 통해 answer배열을 업데이트한다. 이때 조건은 j-i가 0보다 크거나 같은 경우이고, 조건문 안에서 answer[j]에 answer[j-i]를 더해준다.
- answer[k]를 출력한다. 이는 k원이 되는 경우의 수가 된다.

### 구현
- Python
```python
n, k = map(int, input().split())
coin = []
for i in range(n):
    coin.append(int(input()))
answer = [0]*(k+1)
answer[0] = 1
for i in coin:
    for j in range(i, k+1):
        if j-i>=0:
            answer[j] += answer[j-i]
print(answer[k])
```
- C++
```cpp
#include <iostream>
#include <cstring>
#define MAX 10001
#define CMAX 101
using namespace std;

int n, k;
int coin[CMAX];
int answer[MAX];

void Input(){
    cin>>n>>k;
    for(int i=0; i<n; i++){
        cin>>coin[i];
    }
    memset(answer, 0, MAX);
    answer[0]=1;
}

void Solution(){
    for(int i=0; i<n; i++){
        for(int j=coin[i]; j<=k; j++){
            if(j-coin[i]>=0)
                answer[j]+=answer[j-coin[i]];
        }
    }
    cout<<answer[k]<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solution();
    return 0;
}
```

## 3. 연속합 2
https://www.acmicpc.net/problem/13398
### 접근방법
이번 문제는 다이나믹 프로그래밍을 응용하여 해결하였다. 처음에는 하나의 수를 제거할 수 있다는 점에서 단순하게 cnt라는 변수를 0으로 두고, dp[i]>dp[i]+arr[i+1]일 때 cnt를 1 증가시켜 하나의 수를 제거한 것으로 처리를 하였다. 의도한 내용은 잘 작동하였지만 주어진 예제 10, -4, 3, 1, 5, 6, -35, 12, 21, -1에서 3, 1, 5, 6, 12, 21의 합이 결과로 도출되었다. 이를 두고 생각해보니 10에서 -4로 넘어갈 때 cnt가 증가하였기 때문에 -35에서 끝나버리게 되고, 3에서 시작하면 -35를 빼고 21까지 더해지는 결과가 나온다는 것을 깨달았다. 고민 끝에 dp를 2차원 배열로 하여 처리하기로 하였다.

- n을 입력받는다.
- 임의의 수열 arr을 입력받는다.
- 다이나믹 프로그래밍을 위한 배열 dp를 2차원으로 하여 n만큼 할당한다. dp[x][0]은 수를 제거하지 않은 상태에서의 합이고, dp[x][1]은 수를 제거한 상태에서의 합을 의미한다.
- dp[0][0]에는 arr의 첫번째 수를, dp[0][1]에는 임의의 매우 작은 수를 입력한다.
- arr에 음수만 들어갈 수 있기 때문에 answer은 임의의 매우 작은 수로 정의한다.
- 1부터 n까지의 for문을 돌린다.
-> dp[i][0]에는 dp[i-1][0]+arr[i]와 arr[i] 중 더 큰값으로 갱신한다.
-> dp[i][1]에는 dp[i-1][0]과 dp[i-1][1]+arr[i] 중 더 큰 값으로 갱신한다.
- 0부터 n까지의 for문을 돌린다.
-> answer에 내장함수 max를 사용하여 answer과 dp[i] 중 더 큰 값으로 갱신한다.
- answer를 출력한다.

### 구현
- Python
```python
n=int(input())
arr=list(map(int, input().split()))
dp= [[0, 0] for i in range(n)]
dp[0]=[arr[0], -999999999]
answer=-999999999
for i in range(1, n):
    dp[i][0]=max(dp[i-1][0]+arr[i], arr[i])
    dp[i][1]=max(dp[i-1][0], dp[i-1][1]+arr[i])
for i in range(n):
    answer=max(answer, max(dp[i]))
print(answer)
```
- C++
```cpp
#include <iostream>
#include <algorithm>
#define MAX 100001
using namespace std;

int n;
int arr[MAX];
int dp[MAX][2];
int answer=-999999999;

void Input(){
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>arr[i];
        dp[i][0]=arr[i];
        dp[i][1]=-999999999;
    }
}

void Solution(){
    for(int i=1; i<n; i++){
        dp[i][0]=max(dp[i-1][0]+arr[i], arr[i]);
        dp[i][1]=max(dp[i-1][0], dp[i-1][1]+arr[i]);
    }
    for(int i=0; i<n; i++){
        answer=max(answer, max(dp[i][0], dp[i][1]));
    }
    cout<<answer<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solution();
    return 0;
}
```
