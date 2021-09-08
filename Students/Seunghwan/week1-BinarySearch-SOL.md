# 1주차 이진탐색 문제풀이
- 소수 사이 수열
- 히오스 프로게이머
- 두 배열의 합
- 구간 나누기 2
- 휴게소 세우기

## 1. 소수 사이 수열
https://www.acmicpc.net/problem/3896 
### 접근방법
이번 문제는 이분 탐색을 통해 해결하였다.

- 소수들을 먼저 벡터에 넣어준다.
- 소수를 판별하는 기준은 이중 for문에서 합성수에 방문표시를 하여 방문되지 않은 수를 소수로 인지한다.
- 주어진 k보다 큰 첫번째 소수를 찾고, 그 소수와 그 앞의 소수의 차를 출력한다.
- 만약 k의 방문 여부가 false라면 바로 바로 0을 출력한다.
처음에는 약수의 갯수를 반환하는 함수를 만들어 이를 통해 소수와 합성수를 구분하게 하였다. 그러나 이 방식은 시간 초과가 발생하였다. 시간을 줄일 수 있는 방법을 생각해보다가 결국은 구글링을 통해 찾아 해결하였다.

check_Prime함수에서 소수와 합성수를 구분한다.

- i=2일때 check[4], check[6], check[8], ... 과 같은 2의 배수들이 모두 합성수로 표시된다.
- i=3일때 check[6], check[9], check[12], ... 과 같은 3의 배수들이 모두 합성수로 표시된다.
- 이 과정이 범위끝까지 반복되면서 소수와 합성수를 check로 표시하게 된다.
get_Prime함수에서 소수를 prime 벡터에 넣는다.

BinarySearch함수에서 입력 받은 값과 가장 가깝고 큰 소수를 이분탐색으로 찾는다.
### 구현
```c++
#include <iostream>
#include <vector>
#define MAX 1299709+1
using namespace std;

int n;
int a;
vector<int> prime;
bool check[MAX];

void Input(){
    cin>>a;
}

void check_Prime(){
    for(int i=2; i<=MAX; i++){
        if(check[i]) continue;
        for(int j=i+i; j<MAX; j+=i){
            check[j]=true;
        }
    }
}

void get_Prime(){
    for(int i=2; i<=MAX; i++){
        if(!check[i]){
            prime.push_back(i);
        }
    }
}

int BinarySearch(int key){
    int front = 2;
    int back = prime.size()-1;
    while(front<=back){
        int mid = (front+back)/2;
        if(prime[mid]>=key){
            back = mid - 1;
        }
        else{
            front = mid + 1;
        }
    }
    return front;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    check_Prime();
    get_Prime();
    for(int i=0; i<n; i++){
        Input();
        if(!check[a]){
            cout<<0<<endl;
        }
        else{
            int idx = BinarySearch(a);
            int result =prime[idx]-prime[idx-1];
            cout<<result<<endl;
        }
    }
}
```

## 2. 히오스 프로게이머
https://www.acmicpc.net/problem/16564

### 접근방법
이번 문제는 이분탐색을 통해 해결하였다.
- 우선 범위가 최대 10억이므로 자료형은 long long을 사용한다.
- 입력받은 x중 가장 작은 수를 사용해야 하므로 오름차순으로 sort해준다.
- 이분탐색의 범위는 가장 작은 수인 x[0]과 x[0]이 될 수 있는 수 중 가장 큰 수인 x[0]+k로 잡는다.
- mid를 최소값으로 하기 위한 과정에서 필요한 수를 cnt변수에 담는다. 이때 k를 넘어가도 상관없다.
- cnt가 k보다 크다면 결과값이 현재 mid보다 작아야 하므로 back에 mid-1을 넣어준다.
- cnt가 k보다 작거나 같다면 front에 mid+1을 넣어준다.

### 구현
```c++
#include <iostream>
#include <algorithm>
#define MAX 1000001
using namespace std;

int n;
long long k;
long long x[MAX];
long long cnt=0;
long long result=0;

void Input(){
    cin>>n>>k;
    for(int i=0; i<n; i++){
        cin>>x[i];
    }
    sort(x, x+n);
}

void BinarySearch(){
    long long front = x[0];
    long long back = x[0]+k;
    while(front<=back){
        long long mid = (front+back)/2;
        cnt=0;
        for(int i=0; i<n; i++){
            if(mid>x[i]){
                cnt+=(mid-x[i]);
            }
            else break;
        }
        if(cnt>k){
            back=mid-1;
        }
        else{
            result=mid;
            front=mid+1;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    BinarySearch();
    cout<<result<<endl;
    return 0;
}
```

## 3. 두 배열의 합
https://www.acmicpc.net/problem/2143

### 접근방법
이번 문제는 누적합을 구한 뒤에 이분탐색을 통해 경우를 찾는 문제였다. 여러번 시도 끝에 해결하였는데 처음에는 다음과 같이 작성하였고 오답처리 당했다.
- 배열 a,b에 대한 누적합 배열 asum, bsum을 구하고 이를 정렬한다.
- 누적합 배열 asum에 대해서 이분탐색을 누적합 배열 bsum의 길이만큼 반복한다. 이때 이분탐색함수의 인자로 들어가는 vb는 bsum의 원소가 된다.
- asum과 vb의 합이 t가 될 때 cnt를 증가시킨다.
여기서 놓친 부분은 누적합 배열에 같은 수가 있을 수 있다는 점이었다. 같은 수의 갯수를 찾기 위해 이분탐색을 두 번 진행하였다.
- 배열 a,b에 대한 누적합 배열 asum, bsum을 구하고 이를 정렬한다.
- asum에 대한 이분탐색을 두 번 진행한다. 이때 첫번째 이분탐색에서는 같은 수의 가장 앞 인덱스를 lb에 저장하고, 두번째 이분탐색에서는 같은 수의 가장 뒤 인덱스를 ub에 저장한다.
- 두번의 이분탐색이 끝나면 cnt에 ub-lb+1의 값을 더해준다.

### 구현
```c++
#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 1001
using namespace std;

long long t;
int n, m;
int a[MAX], b[MAX];
vector<long long> asum, bsum;
long long cnt=0;

void Input(){
    cin>>t>>n;
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    cin>>m;
    for(int j=0; j<m; j++){
        cin>>b[j];
    }
}

void GetSum(){
    for(int i=0; i<n; i++){
        int sum=0;
        for(int j=i; j<n; j++){
            sum+=a[j];
            asum.push_back(sum);
        }
    }
    sort(asum.begin(), asum.end());
    for(int i=0; i<m; i++){
        int sum=0;
        for(int j=i; j<m; j++){
            sum+=b[j];
            bsum.push_back(sum);
        }
    }
}

void BinarySearch(long long vb){
    long long front=0;
    long long back=asum.size()-1;
    long long ub=-1;
    long long lb=-1;
    while(front<=back){
        long long mid=(front+back)/2;
        if(asum[mid]+vb>=t){
            if(asum[mid]+vb==t){
                lb=mid;
            }
            back=mid-1;
        }
        else if(asum[mid]+vb<t){
            front=mid+1;
        }
    }
    front=0, back=asum.size()-1;
    while(front<=back){
        long long mid=(front+back)/2;
        if(asum[mid]+vb>t){
            back=mid-1;
        }
        else if(asum[mid]+vb<=t){
            if(asum[mid]+vb==t){
                ub=mid;
            }
            front=mid+1;
        }
    }
    if(ub!=-1&&lb!=-1){
        cnt+=(ub-lb+1);
    }
}

void Solution(){
    for(int i=0; i<bsum.size(); i++){
        BinarySearch(bsum[i]);
    }
    cout<<cnt<<endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    GetSum();
    Solution();
    return 0;
}
```

## 4. 구간 나누기 2
https://www.acmicpc.net/problem/13397

### 접근방법
이번 문제는 이분탐색을 통해 해결하는 문제였다. 이분탐색의 범위에 대해서 고민을 많이 했던 것 같다. 이분탐색의 범위는 0과 배열의 최대값으로 하였다.
- 배열을 돌며 해당 인덱스에서의 최대값-최소값의 값이 mid보다 크다면 cnt를 증가시켜주고, cnt가 m보다 작거나 같으면 true, 아니라면 false를 반환하는 bool형 함수 Check를 작성한다. 이때, cnt가 증가하면 그 인덱스를 저장하고, 그 다음에 돌때는 저장된 인덱스 이후부터 돌도록 한다.(구간을 나누는 것을 구현)
- 이분탐색 시 front에 0을, back에 배열의 최대값을 넣고, while문의 조건은 front<=back으로 둔다. (모든 경우 확인)
- 매 반복마다 Check함수의 반환값이 true이면, result에 mid를 넣어준다.
- result에 결과가 저장된다.

### 구현
```c++
#include <iostream>
#include <algorithm>
#define MAX 5001
using namespace std;

int n, m;
int arr[MAX];

void Input(){
    cin>>n>>m;
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
}

bool Check(int mid){
    int cnt=1;
    int mini=10001;
    int maxi=0;
    int idx=-1;
    for (int i=idx+1; i<n; i++){
        mini=min(mini, arr[i]);
        maxi=max(maxi, arr[i]);
        if(maxi-mini>mid){
            cnt++;
            mini=arr[i];
            maxi=arr[i];
            idx=i;
        }
    }
    return cnt<=m;
}

int Solution(){
    int big=0;
    for(int i=0; i<n; i++){
        big=max(big, arr[i]);
    }
    int result=0;
    int front=0;
    int back=big;
    while(front<=back){
        int mid=(front+back)/2;
        if(Check(mid)){
            result=mid;
            back=mid-1;
        }
        else
            front=mid+1;
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    cout<<Solution()<<endl;
    return 0;
}
```

## 5. 휴게소 세우기
https://www.acmicpc.net/problem/1477

### 접근방법
이번 문제는 이분탐색으로 해결하는 문제였다. 처음에는 이분탐색으로 해결하는 방법이 생각이 안나서 이분탐색을 빼고 생각해보았다.
- 각 휴게소 간의 거리 배열 dis를 만든다.
- dis를 내림차순으로 정렬한다.
- 가장 큰 거리를 반으로 자른다. (휴게소를 사이에 세운다.)
- dis를 다시 내림차순으로 정렬한다. 이 과정을 m번 반복한다.
이 방식의 문제점은 가장 큰 거리를 반으로 나눴을 때도 그 나눈 거리가 가장 큰 거리일 때 발생한다. m이 부족하다면 남은 거리를 나누지 못하게 되어 최대거리가 커지게 된다.
이분탐색으로 해결할 수 있는 방식을 다시한번 생각해보았고, 구글의 힘을 조금 빌려 문제를 해결할 수 있었다.
- 각 휴게소 간의 거리 배열 dis를 만든다.
- dis를 내림차순으로 정렬한다.
- 이분탐색을 하는데, front에 1을, back에 l-1을 대입하고 시작한다. 다른 이분탐색과 다른점은 while문의 조건이 front<back-1이라는 점이다.
- 만약 mid가 dis보다 작은 경우 dis가 mid에 나눠 떨어지는지 확인하고, 나눠떨어진다면 cnt에 dis/mid-1을 더해주고, 나눠 떨어지지 않는다면 dis/mid를 더해준다. 매 루프마다 나오는 mid값이 휴게소 간 거리의 최대값이 되기 때문에 dis/mid-1 혹은 dis/mid개의 휴게소를 설치하는 것을 구현한 것이다.
- mid와 dis를 비교하고 난 뒤에 cnt와 m을 비교한다. cnt가 m보다 크다면 front에 mid를 넣어주고, cnt가 m보다 작으면 back에 mid를 넣어준다. 어떻게 보면 구간을 나누는 과정이기 때문에 mid-1이나 mid+1을 대입하지 않는다. (이 때문에 while문의 조건문도 front<back-1이 된다.)
- 이분탐색은 back에 저장된 값을 반환한다.

### 구현
```c++
#include <iostream>
#include <algorithm>
#define MAX 101
using namespace std;

int n, m, l;
int point[MAX];
int dis[MAX];

void Input(){
    cin>>n>>m>>l;
    for(int i=0; i<n; i++){
        cin>>point[i];
    }
    sort(point, point+n);
}

void GetDistance(){
    dis[0]=point[0];
    for(int i=1; i<n; i++){
        dis[i]=point[i]-point[i-1];
    }
    dis[n]=l-point[n-1];
}

int BinarySearch(){
    int front=1;
    int back=l-1;
    while(front<back-1){
        int mid=(front+back)/2;
        int cnt=0;
        for(int i=0; i<=n; i++){
            if(dis[i]>mid){
                if(dis[i]%mid==0){
                    cnt+=dis[i]/mid-1;
                }
                else{
                    cnt+=dis[i]/mid;
                }
            }
        }
        if(m<cnt){
            front=mid;
        }
        else{
            back=mid;
        }
    }
    return back;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Input();
    GetDistance();
    cout<<BinarySearch()<<endl;
    return 0;
}
```
