## 1주차 이진탐색 문제풀이

- 소수 사이 수열
- 히오스 프로게이머
- 두 배열의 합
- 구간 나누기2
- 휴게소 세우기

### 1. 소수 사이 수열

**문제**

[소수 사이 수열 바로가기](https://www.acmicpc.net/problem/3896)

**접근방법**

입력되는 정수 `k`보다 크면서 가장 가까운 소수값을 찾는것이 이번 문제의 관건이었다.
때문에 소수 여부를 판단해 주는 `isPrime`함수를 선언하여 1 ~ 1299709 까지의 값 중 소수인 값만을 벡터 `prime`에 저장해 주었다.

만약 `k`가 소수이면 바로 0을 출력하고

`k`가 합성수라면 `lower_bound`함수를 사용하여 k보다 크면서 가장 가까운 소수의 인덱스 값을 알아내어 해당 인덱스의 소수값 `ans2 = prime[idx]`과 그 바로앞의 인덱스의 소수값 `ans1 = prime[idx-1]`을 구한 후

두 수의 차를 구해서 k를 포함하는 소수 사이 수열의 길이를 구할 수 있었다.

**구현**

``` cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> prime;

bool isPrime(int num)
{
    if(num == 2) return true;
    if(num%2 == 0) return false;
    for(int i=3; i<sqrt(num)+1; i++)
    {
        if(num%i == 0) return false;
    }
    return true;
}

int main(void)
{
    int tc, k;
    int ans1, ans2;
    int idx;

    for(int i=1; i<=1299709; i++)
    {
        if(isPrime(i)) prime.push_back(i); 
    }

    cin>>tc;
    while(tc--)
    {
        ans1=ans2=0;
        cin>>k;
        if(isPrime(k))
        {
            cout<<0<<'\n';
            continue;
        }

        idx = lower_bound(prime.begin(), prime.end(), k) - prime.begin();
        ans1 = prime[idx-1];
        ans2 = prime[idx];
        
        cout<<ans2-ans1<<'\n';
    }
    return 0;
}
```

### 2. 히오스 프로게이머

**문제**


[히오스 프로게이머 바로가기](https://www.acmicpc.net/problem/16564)

**접근방법**

`upper_bound(x.begin(), x.end(), Min) - x.begin();` 는 n개의 레벨중에서 가장 작은수 다음으로 큰 값의 인덱스를 반환하고 이는 가장 작은수의 개수와 같다.

즉 배열 x에 가장 작은 레벨이 총 `minNum`개 존재한다.

이때 주의해야 할 것이, 만약 upper_bound를 사용하여 키값을 탐색할때, 해당 키값이 배열에 존재하지 않으면 `x.end()`, 즉 값이 저장되지 않은 끝의 `n`을 반환하게 된다. 때문에 "Out of bound" 에러에 의한 런타임 에러를 주의해야 한다.

때문에 다음과 같은 예외 처리문을 넣어주었다.
``` cpp
if(minNum==n) nextNum = x[minNum-1];
else nextNum = x[minNum];
```

만약 최소값들에 minNum 만큼 k를 분배할때 최소값이 그보다 바로 큰값과 같아지게 된다면 최소값을 nextNum으로 갱신하고 위의 과정을 반복한다.

k를 minNum 만큼 각각의 최소값에 전부 분배해도 최소값이 nextNum보다 여전히 작다면 모든 k를 minNum개 만큼 나눠서 최소값에 더해주면 Min이 가능한 최소레벨 값이 된다.

**구현**

``` cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);
    int n, k, level;
    int Min, minNum;
    vector<int> x;

    cin>>n>>k;

    if(n==1)
    {
        cout<<n+k<<'\n';
        return 0;
    }

    for(int i=0; i<n; i++)
    {
        cin>>level;
        x.push_back(level);
    }

    sort(x.begin(), x.end());
    Min = x[0];
    
   minNum = upper_bound(x.begin(), x.end(), Min) - x.begin(); 

    while(1)
    {
        int nextNum;
        if(minNum==n) nextNum = x[minNum-1];
        else nextNum = x[minNum];

        if((Min + (k/minNum)) >= nextNum && minNum!=n)
        {
            k = k - (minNum * (nextNum - Min));
            Min = nextNum;
            minNum = upper_bound(x.begin(), x.end(), Min) - x.begin(); 
        }
        else
        {
            k/=minNum;
            Min += k;
            break;
        }
    }

    cout<<Min<<'\n';
    return 0;
}
```

### 3. 두 배열의 합

**문제** 

[두 배열의 합 바로가기](https://www.acmicpc.net/problem/2143)

**접근방법**

각 배열 a,b의 부분 합을 저장하는 배열 sA, sB를 각각 선언해준 다음 각각 오름차순으로 정렬 해주고 나서 이진탐색을 활용하여 T - sA[i]를 만족하는 수가 sB에 몇개 존재하는 지를 총합해서 구하는 방식으로 해결하였다.

`배열 a`의 부분 합을 저장하는 배열 sA = {a[0], a[0]+a[1], a[0]+a[1]+a[2], ..., a[0]+ ... a[n]} 를 선언해 주고 마찬가지로 배열 b의 부분 합의 배열 sB도 선언해 주었다.

아래의 반복문을 통해 T를 만족하는 a,b의 부분 합을 구할 수 있다.

``` cpp
for(int i=0; i<sA.size(); i++)
{
    left = lower_bound(sB.begin(), sB.end(), t - sA[i]) - sB.begin();
    right = upper_bound(sB.begin(), sB.end(), t - sA[i]) - sB.begin();
    cnt += right - left;
}
```

**구현**

``` cpp
#include<iostream>
#include<vector>
#include<algorithm>
typedef long long ll;
using namespace std;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);
    int t, n, m, num, left, right;
    ll sum = 0;
    ll cnt = 0;
    vector<int> a, b;
    vector<ll> sA, sB;
    cin>>t;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>num;
        a.push_back(num);
    }

    cin>>m;
    for(int i=0; i<m; i++)
    {
        cin>>num;
        b.push_back(num);
    }

    for(int i=0; i<n; i++)
    {
        sum = a[i];
        sA.push_back(sum);
        for(int j=i+1; j<n; j++)
        {
            sum += a[j];
            sA.push_back(sum);
        }
    }

    for(int i=0; i<m; i++)
    {
        sum = b[i];
        sB.push_back(sum);
        for(int j=i+1; j<m; j++)
        {
            sum += b[j];
            sB.push_back(sum);
        }
    }

    sort(sA.begin(), sA.end());
    sort(sB.begin(), sB.end());

    for(int i=0; i<sA.size(); i++)
    {
        left = lower_bound(sB.begin(), sB.end(), t - sA[i]) - sB.begin();
        right = upper_bound(sB.begin(), sB.end(), t - sA[i]) - sB.begin();
        cnt += right - left;
    }

    cout<<cnt<<'\n';
    return 0;
}
```

### 4. 구간 나누기2

**문제** 

[구간 나누기2 바로가기](https://www.acmicpc.net/problem/13397)

**접근방법**

이분탐색을 사용하여 구간의 최대 최소값을 mid값으로 놓고 구간에 대한 제한조건을 만족하는 최소 mid값을 정답으로 출력하여 문제를 해결하였다.

구간에 대한 제한조건은 `check`함수를 통해 구현하였으며 구간내의 최대, 최소값의 차인 구간 점수를 `mid`라고 가정하였을때,
만약 구간 점수가 가정한 mid값을 넘어가면 `(if(Max - Min > mid))` 구간을 나눠 주었다.

만약 check 함수내에서 생성된 구간이 m이하여서 제한조건을 만족한다면 true를 반환하여 정답값을 갱신해주면서 오른쪽 구간을 좁혀주었다. `(right = mid - 1)`
때문에 갱신되는 정답(ans)값은 기존값보다 작은 값이 되어 구간의 점수의 최댓값을 최소로하는 것이 가능하다.

만약 check 함수에 의해 구간 점수를 mid로 하였을때 구간이 m보다 많이 생기게 된다면 구간 점수값을 증가시켜서 구간이 m이하가 되도록 해주었다. `(left = mid + 1)`

**구현**

``` cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> v;
int cnt;
int n, m;

bool check(int mid)
{
    int Max, Min;
    Max = Min = v[0];
    int idx = 0;
    for(int i=idx+1; i<n; i++)
    {
        Max = max(Max, v[i]);
        Min = min(Min, v[i]);

        if(Max - Min > mid)
        {
            Max = Min = v[i];
            cnt++;
            idx = i;
        }
    }
    if(cnt<=m) return true;
    else return false;
}

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);
    int num;
    int left = 0, right = 0;
    int mid, ans;

    cin>>n>>m;

    for(int i=0; i<n; i++)
    {
        cin>>num;
        v.push_back(num);
        right = max(right, num);
    }

    while(left <= right)
    {
        cnt = 1;
        mid = (left+right)/2;
        if(check(mid))
        {
            ans = mid;
            right = mid - 1;
        }
        else left = mid + 1;
    }
    cout<<ans<<'\n';
    return 0;
}
```

### 5. 휴게소

**문제** 

[휴게소 세우기 바로가기](https://www.acmicpc.net/problem/1477)

**접근방법**

휴게소간 거리가 가장 긴 구간을 기준으로 이분탐색을 사용하여 휴게소가 없는 구간의 최댓값의 최솟값을 mid라고 가정하고 문제를 접근하였다.

서로 인접한 휴게소들 간의 거리가 v[i-1], v[i]일때, 그 사이에 세워야하는 휴게소의 개수는 `cnt += (v[i]-v[i-1]-1) / mid`이 된다.

만약 mid를 기준으로 설치한 총 휴게소의 개수가 M보다 크다면 왼쪽구간을 오른쪽으로 좁혀서 mid의 값을 키워서 휴게소 개수를 줄여준다.

cnt가 M보다 크지 않다면 휴게소가 없는 구간의 최댓값의 최솟값을 갱신해 준다음 구간을 좁혀서 반복한다. 

이분탐색을 통해 구간의 최댓값의 최솟값을 구하게 된다면 cnt가 M미만이어도 휴게소를 임의의 구간에 아무렇게나 설치해도 되므로 상관없다.

`(v[i]-v[i-1]-1) / mid` 에서 -1을 해주는 이유를 극단적인 예로 설명을 하자면, 만약 mid = 1이고 두 휴게소가 1, 2에 연속해서 존재할때, -1을 생략하면 1/1 = 1로 두 휴게소 사이에 하나의 휴게소를 추가할 수 있다는 오류를 범하게 된다.

**구현**

``` cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> v;

int main(void)
{
    ios::sync_with_stdio(false); cin.tie(0);
    int N, M, L;
    int loc, cnt;
    int ans = 0;
    int left, mid, right;
    left=right=mid=0;
    v.push_back(0);

    cin>>N>>M>>L;

    for(int i=1; i<=N; i++)
    {
        cin>>loc;
        v.push_back(loc);
    }
    v.push_back(L);
    sort(v.begin(), v.end());

    for(int i=1; i<v.size(); i++)
    {
        right = max(right, v[i] - v[i-1]);  // 휴게소간 거리가 가장 긴 구간을 찾음
    }

    while(left <= right)
    {
        cnt = 0;
        mid = (left+right)/2;
        for(int i=1; i<v.size(); i++) cnt += (v[i]-v[i-1]-1) / mid;

        if(cnt > M) left = mid+1;
        else
        {
            ans = mid;
            right = mid-1;
        }
    }

    cout<<ans<<'\n';
    return 0;
}
```