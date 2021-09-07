# 1주차 이진탐색 문제풀이

- 소수 사이 수열
- 히오스 프로게이머
- 두 배열의 합
- 휴게소 세우기

## 1. 소수 사이 수열

https://www.acmicpc.net/problem/3896

### 접근방법

-

### 구현

```c++
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;
//10 -> 7~11 사이 길이:4
//11 -> 소수 -> 길이:0
//27 -> 23~29 길이:6
//2 -> 소수 -> 길이:0

int number = 1299709;
int a[1299710];//100000번째 소수 1299709 ->미리 배열 선언
vector<int> prime;//primenum만 존재

int binarySearch(int n) {
    int low = 2;//2와 3은 걸러지기 때문.
    int high = prime.size() - 1;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (prime[mid] >= n)high = mid - 1;
        else low = mid + 1;
    }
    return low;
}

int main() {
    int caseNum;
    int i = 0;
    scanf("%d", &caseNum);//test case 수 입력
    int* arr = new int[caseNum];
    a[0] = 0;//0과 1은 not prime num -> 0으로 초기화
    a[1] = 0;
    for (int i = 2; i <= number; i++) {
        a[i] = i;
    }
    //에라토스테네스의 체
    for (int i = 2; i <= number; i++) {
        for (int j = i + i; j <= number; j += i) {
            a[j] = 0;//prime num 아니기 때문에 0 set
        }
    }
    for (int i = 2; i <= number; i++) {
        if (a[i]) prime.push_back(i);
    }
        for (i = 0; i < caseNum; i++) {
            scanf("%d", &arr[i]);
        }
        for (i = 0; i < caseNum; i++) {
            if (a[arr[i]])//0이 아니면(소수이면)
                printf("0\n");
            else {
                int index = binarySearch(arr[i]);
                printf("%d\n", prime[index] - prime[index-1]);
            }
        }

    delete[] arr;
    return 0;
}
```

## 2. 히오스 프로게이머

https://www.acmicpc.net/problem/16564

### 접근방법

-

### 구현

```c++
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    long long n, k;//n은 캐릭터 수, k는 올릴 수 있는 레벨 총합
    scanf("%lld %lld", &n, &k);
    long long* character = new long long[n];//각 캐릭터 레벨
    for (int i = 0; i < n; i++) {
        scanf("%lld", &character[i]);
    }

    sort(character, character + n);

    long long min, num, dif, t;

    while (1) {
        min = character[0];
        //num은 min값에 해당하는 수의 개수(or 인덱스번호)
        num = upper_bound(character, character + n, min) - character;
        /*num = upper_bound(character, character + n, min) - lower_bound(character, character+n,min);
        했을 시 틀림*/

        dif = (character[num] - min) * num;
        if (dif <= k) {
            character[0] += dif / num;
        }
        else {//dif>k
            t = min + k / num;
            break;
        }
        k -= dif;
    }
    printf("%lld\n", t);//가능한 최대 팀 목표레벨 t
    delete[]character;
    return 0;
}
```

## 3. 두 배열의 합

https://www.acmicpc.net/problem/2143

### 접근방법

### 구현

```c++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    long long t;
    int n, m;
    long long cnt = 0;
    int sum = 0;

    scanf("%lld", &t);//부 배열의 합에 해당하는 값
    scanf("%d", &n);
    int* a = new int[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    scanf("%d", &m);
    int* b = new int[m];
    for (int i = 0; i < m; i++) {
        scanf("%d", &b[i]);
    }
    vector <int> A, B;
    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            A.push_back(sum);//모든 부분합 저장하는 벡터
        }
    }
    for (int i = 0; i < m; i++) {
        sum = 0;
        for (int j = i; j < m; j++) {
            sum += b[j];
            B.push_back(sum);
        }
    }
    /* 메모리 초과
    int tmp1 = (n * (n + 1)) / 2;
    int tmp2 = (m * (m + 1)) / 2;
    for (int i = 0; i < tmp1; i++) {
        for (int j = 0; j < tmp2; j++) {
            C.push_back(A[i] + B[j]);
        }
    }
    sort(C.begin(), C.end());
    cnt = upper_bound(C.begin(), C.end(), t)- lower_bound(C.begin(), C.end(), t);
    printf("%d\n", cnt);
    */
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    long long low1 = 0, high1 = A.size() - 1;
    long long low2 = 0, high2 = B.size() - 1;
    while (low1<=high1 && low2<=high2) {
        sum = A[low1] + B[high2];
        if (sum < t)low1++;
        else if (sum == t) {
            long long c1 = 1, c2 = 1;
            c1 = upper_bound(A.begin(), A.end(), A[low1]) - lower_bound(A.begin(), A.end(), A[low1]);
            c2 = upper_bound(B.begin(), B.end(), B[high2]) - lower_bound(B.begin(), B.end(), B[high2]);
            cnt += c1 * c2;
            low1 += c1;
            high2 -= c2;

        }
        else high2--;//sum>t일 때
    }
    printf("%lld\n", cnt);
    delete[]a;
    delete[]b;
    return 0;
}
```

## 5. 휴게소 세우기

https://www.acmicpc.net/problem/1477

### 접근방법

-

### 구현

```c++
#include <iostream>
#include <algorithm>

int main() {
	int rest[202];//총 휴게소 수<=200
	int n, m, l;//n:현재 휴게소 개수, m:더 지으려는 휴게소 개수, l:고속도로 길이
	scanf("%d %d %d", &n, &m, &l);
	if (n < 1 || n>100)//n<=100
		return -1;
	else if (m < 1 || m>100)//m<=100
		return -1;
	else if (l < 100 || l>1000)//100<=l<=1000
		return -1;
	else if (n + m >= l)//n+m < l
		return -1;
	rest[0] = 0;//시작점
	rest[n + 1] = l;//끝점
	for (int i = 1; i < n + 1; i++) {//휴게소 위치 입력
		scanf("%d", &rest[i]);
	}
	std::sort(rest, rest + n + 1);//작은 수부터 왼쪽정렬
	int max = 0;
	for (int j = 0; j < n + 1; j++) {//최대거리 구하고
		if (max < rest[j + 1] - rest[j]) {
			max = rest[j + 1] - rest[j];
		}
	}
	int start = 1, end = max;//(모든 휴게소 사이 거리는 1이상 max이하)
	int mid;
	int cnt;
	while (start <= end) {
		cnt = 0;//휴게소 카운트 초기화
		mid = (end + start) / 2;//binary search
		for (int k = 0; k < n + 1; k++) {
			if (mid <= rest[k + 1] - rest[k]) {
				cnt += ((rest[k + 1] - rest[k]) / mid);// mid로 나눈 몫 만큼 휴게소 추가
			}
			if (((rest[k + 1] - rest[k]) % mid) == 0) {// 두 휴게소 사이거리가 mid로 나누어 떨어질 경우 cnt--해주어야
				cnt--;
			}
		}
		if (cnt > m) {//더 지으려는 휴게소 갯수보다 크면 cnt 줄여야 하기 때문에
			start = mid + 1;
		}
		else {//더 지으려는 휴게소 갯수와 작거나 같으면 cnt 늘려야
			end = mid - 1;
		}
	}
	printf("%d", start);
	return 0;
}
```
