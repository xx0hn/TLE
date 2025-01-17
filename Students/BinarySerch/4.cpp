/*
 문제
 N개의 수로 이루어진 1차원 배열이 있다. 이 배열을 M개 이하의 구간으로 나누어서 구간의 점수의 최댓값을 최소로 하려고 한다. 구간은 다음과 같은 조건을 만족해야 한다.
     하나의 구간은 하나 이상의 연속된 수들로 이루어져 있다.
     배열의 각 수는 모두 하나의 구간에 포함되어 있어야 한다.
 구간의 점수란 구간에 속한 수의 최댓값과 최솟값의 차이이다.
 예를 들어, 배열이 [1, 5, 4, 6, 2, 1, 3, 7] 이고, M = 3인 경우가 있다.
 이때, [1, 5], [4, 6, 2], [1, 3, 7]로 구간을 나누면 각 구간의 점수는 4, 4, 6점이 된다. 이때, 최댓값은 6점이다.
 만약, [1, 5, 4], [6, 2, 1], [3, 7]로 구간을 나누었다면, 각 구간의 점수는 4, 5, 4점이 되고, 이때 최댓값은 5점이 된다.
 두 경우 중에서 최댓값이 최소인 것은 5점인 것이고, 5점보다 최댓값을 작게 만드는 방법은 없다.
 배열과 M이 주어졌을 때, 구간의 점수의 최댓값의 최솟값을 구하는 프로그램을 작성하시오.
 ####입력####
 첫째 줄에 배열의 크기 N과 M이 주어진다. (1 ≤ N ≤ 5,000, 1 ≤ M ≤ N)
 둘째 줄에 배열에 들어있는 수가 순서대로 주어진다. 배열에 들어있는 수는 1보다 크거나 같고, 10,000보다 작거나 같은 자연수이다.
 ####출력####
 첫째 줄에 구간의 점수의 최댓값의 최솟값을 출력한다.
 */
/*
이번 문제는 이분탐색을 통해 해결하는 문제였다. 이분탐색의 범위에 대해서 고민을 많이 했던 것 같다. 이분탐색의 범위는 0과 배열의 최대값으로 하였다.

배열을 돌며 해당 인덱스에서의 최대값-최소값의 값이 mid보다 크다면 cnt를 증가시켜주고, cnt가 m보다 작거나 같으면 true, 아니라면 false를 반환하는 bool형 함수 Check를 작성한다. 이때, cnt가 증가하면 그 인덱스를 저장하고, 그 다음에 돌때는 저장된 인덱스 이후부터 돌도록 한다.(구간을 나누는 것을 구현)
이분탐색 시 front에 0을, back에 배열의 최대값을 넣고, while문의 조건은 front<=back으로 둔다. (모든 경우 확인)
매 반복마다 Check함수의 반환값이 true이면, result에 mid를 넣어준다.
result에 결과가 저장된다.
*/
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
