/* 문제
 연속한 소수 p와 p+n이 있을 때, 그 사이에 있는 n-1개의 합성수(소수나 1이 아닌 양의 정수)는 길이가 n인 소수 사이 수열라고 부른다.
 양의 정수 k가 주어졌을 때, k를 포함하는 소수 사이 수열의 길이를 구하는 프로그램을 작성하시오. k를 포함하는 소수 사이 수열이 없을 때는 길이가 0이다.
 예를 들어, 소수 23과 29의 소수 사이 수열은 {24, 25, 26, 27, 28}이고, 길이는 6이다.
 #######입력#######
 첫째 줄에 테스트 케이스의 개수 T가 주어진다. 테스트 케이스는 한 줄로 이루어져 있고, 한 줄에 정수 k가 주어진다. 각각의 정수는 1보다 크고, 100000번째 소수(1299709)와 작거나 같다.
 #######출력#######
 각각의 테스트 케이스에 대해서 k가 합성수라면 k를 포함하는 소수 사이 수열의 길이를 출력한다. 그렇지 않으면 0을 출력한다.
 */
/*
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
- get_Prime함수에서 소수를 prime 벡터에 넣는다.

BinarySearch함수에서 입력 받은 값과 가장 가깝고 큰 소수를 이분탐색으로 찾는다.
*/
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
