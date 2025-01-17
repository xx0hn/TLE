/*
 히오스 프로게이머
 준석이는 Heroes of the Storm 프로게이머 지망생이다.
 이 게임에는 총 N개의 캐릭터가 있다. 그리고 현재 각 캐릭터의 레벨은 Xi이다. 성권이는 앞으로 게임이 끝날 때까지, 레벨을 최대 총합 K만큼 올릴 수 있다.
 팀 목표레벨 T =min(Xi) (1 ≤ i ≤ N)라고 정의하면, 게임이 끝날 때까지 성권이가 달성할 수 있는 최대 팀 목표레벨 T는 무엇인가?
 예를 들어, N = 3, X1= 10, X2= 20, X3= 15이고 K = 10일 때, X1을 7만큼 올리고 X3을 2만큼 올리면 최소 레벨 Xi는 17이 된다. 따라서 팀 목표레벨 T는 17이다.
 이 경우처럼 레벨을 총합 K보다 적게 올릴 수도 있다.
 #######입력#######
 첫째 줄에는 캐릭터의 개수 N, 올릴 수 있는 레벨 총합 K가 주어진다. (1 ≤ N ≤1,000,000, 1 ≤ K ≤ 1,000,000,000)
 다음 N개의 줄에는 현재 각 캐릭터의 레벨이 X1, X2, X3, ... , Xn 으로 주어진다. (1 ≤ Xi ≤ 1,000,000,000)
 #######출력#######
 가능한 최대 팀 목표레벨 T를 출력한다.
 제한시간: 1초
 */
/*
이번 문제는 이분탐색을 통해 해결하였다.

우선 범위가 최대 10억이므로 자료형은 long long을 사용한다.
입력받은 x중 가장 작은 수를 사용해야 하므로 오름차순으로 sort해준다.
이분탐색의 범위는 가장 작은 수인 x[0]과 x[0]이 될 수 있는 수 중 가장 큰 수인 x[0]+k로 잡는다.
mid를 최소값으로 하기 위한 과정에서 필요한 수를 cnt변수에 담는다. 이때 k를 넘어가도 상관없다.
cnt가 k보다 크다면 결과값이 현재 mid보다 작아야 하므로 back에 mid-1을 넣어준다.
cnt가 k보다 작거나 같다면 front에 mid+1을 넣어준다.
*/
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
