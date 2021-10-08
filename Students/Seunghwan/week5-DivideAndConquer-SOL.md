# 5주차 분할정복 문제풀이
- Moo 게임
- 별 찍기 - 11

## 1. Moo 게임
https://www.acmicpc.net/problem/5904
### 접근방법
이번 문제는 분할정복으로 해결하였다. 처음에는 재귀방식으로 Moo배열을 만들어 주려고 생각을 했었다. 그러나 구현하던 도중에 n의 범위가 10억이기 때문에 메모리 초과가 발생한다는 사실을 알게 되었다.

그래서 Moo배열의 길이를 이용하여 길이가 n보다 크거나 같을 때까지 Moo 배열의 길이를 증가 시킨 뒤에 s(k-1), m+o*(k+2), s(k-1) 중에 어디에 속하는지 확인한 뒤에 그 범위 내에서 글자를 구하였다.

- Moo배열의 길이의 증가에 대한 패턴을 보면 len(2*s(k-1))+(1+k+2)이다. 변수 len에 s(k-1)의 길이를 저장하여 재귀함수의 매 반복마다 Moo배열의 길이를 늘린다.
- n이 3이하라면 moo안에서 해결이 가능하다.
- 새로운 Moo배열의 길이 nlen이 n보다 크거나 같다면 n번째 문자를 구할 수 있다. 이때 n이 기존의 Moo배열의 길이보다 크고, 기존의 Moo배열의 길이+k+3보다 작을 때 (m+o*(k+2)범위일 때) n-기존의 길이가 1이 아니면 o를, 1이라면 m을 출력하도록 한다. n이 m+o*(k+2)범위 외일 때는 범위를 s(k-1)로 줄여 재귀함수를 호출하여 탐색한다.
- 새로운 Moo배열 nlen이 n보다 작다면 Moo배열이 더 길어져야 하므로 재귀함수를 호출하여 길이를 증가시킨다.

### 구현
```c++
#include <iostream>
using namespace std;

long long n;
char s[3]={'m','o','o'};

void Input(){
    cin>>n;
}

void Solution(long long n1, long long k, long long len){
    long long nlen=len*2+k+3;
    if(n1<=3){
        cout<<s[n1-1]<<endl;
        exit(0);
    }
    if(nlen>=n1){
        if(n1>len&&n1<=len+k+3){
            if(n1-len!=1){
                cout<<"o"<<endl;
                exit(0);
            }
            else{
                cout<<"m"<<endl;
                exit(0);
            }
        }
        else{
            Solution(n1-(len+k+3), 1, 3);
        }
    }
    else{
        Solution(n1, k+1, nlen);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solution(n,1,3);
    return 0;
}
```

## 2. 별 찍기 - 11
https://www.acmicpc.net/problem/2448

### 접근방법
이번 문제는 분할 정복으로 해결하였다. 전에 풀어보았던 별 찍기보다 복잡한 형태의 문제여서 고민을 많이 했다. 출력되는 별이 많으므로 2차원 배열에 저장하기로 하였다.

- n의 범위가 3x2^10까지이므로 3072까지 가능하다. 예제 출력을 자세히 보면 가장 위에 별이 가로축에서 n번째에 위치하는 것을 알 수 있으므로 MAX를 (3027+1)*2로 정의해준다. 별을 담는 star배열은 star[MAX/2][MAX]가 된다.
- 재귀함수를 통하여 분할 정복을 해준다.
- 이때 높이에 해당하는 h가 이라면 작은 삼각형을 이루는 별을 배열에 삽입해준다.
- 그 외의 경우에는 각각 현재 위치에서 위, 좌, 우 방향으로 삼각형을 생성해줘야 하므로 h의 절반 값인 nh를 높이로 하여 재귀함수를 호출한다. nh는 재귀함수마다 절반으로 줄어 3이 될때까지 쪼개지고 3이 되면 별을 삽입하게 된다.

### 구현 (C++)
```c++
#include <iostream>
#define MAX 2*(3072+1)
using namespace std;

int n;
char star[MAX/2][MAX];

void Input(){
    cin>>n;
    for(int i=0; i<n+1; i++){
        for(int j=0; j<2*n; j++){
            star[i][j]=' ';
        }
    }
}

void Solution(int h, int y, int x){
    if(h==3){
        star[y][x]='*';
        star[y+1][x-1]='*';
        star[y+1][x+1]='*';
        for(int i=x-2; i<x+3; i++){
            star[y+2][i]='*';
        }
        return;
    }
    else{
        int nh=h/2;
        Solution(nh, y, x);
        Solution(nh, y+nh, x-nh);
        Solution(nh, y+nh, x+nh);
    }
}

void Solve(){
    for(int i=0;i<n;i++){
        for(int j=0; j<2*n-1; j++){
            cout<<star[i][j];
        }
        cout<<endl;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    Solution(n, 0, n-1);
    Solve();
    return 0;
}
```

### 구현 (Python)
```python
n=int(input())
star=[[' ']*2*n for _ in range(n)]
def Solution(h, y, x):
    if h==3:
        star[y][x]='*'
        star[y+1][x-1]='*'
        star[y+1][x+1]='*'
        for i in range(x-2, x+3):
            star[y+2][i]='*'
    else:
        nh=h//2
        Solution(nh, y, x)
        Solution(nh, y+nh, x-nh)
        Solution(nh, y+nh, x+nh)
Solution(n, 0, n-1)
for r in star:
    print("".join(r))
```
