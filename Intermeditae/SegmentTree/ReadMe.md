# 개요
배열 A={a1,a2,a3,a4,...an}에 대하여 A의 부분합을 구하기 위해선 누적합을 사용한다.
```
* Sum(0)=0;
* Sum(i)=a1+a2+a3+...+ai (1<=i<=n) //a1~ai까지의 합
* PartialSum(start,end)=Sum(end)-Sum(start-1) //1<=start<=end<=n  
```
이 과정은 모든 i(1<=i<=n) 에 대하여 Sum(i) 를 미리 구하는 과정은 O(n)이고  
이를 미리 저장해둔다면 partialSum 함수의 수행시간은 O(1) 이다. 
만약 이때 ai (1<=i<=n)이 바뀐다면 Sum(i)~Sum(n) 의 모든 값을 바꿔야 한다.  
즉, 이 과정은 O(n) 의 시간이 걸린다. 그렇다면 빠르게 갱신할 수 있는 방법은 없을까?
# 세그먼트 트리
이는 세그먼트 트리를 이용하면 해결이 가능하다. 여기선 탑-다운 방식의 세그먼트 트리를 다루겠다.  
세그먼트 트리는 말 그대로 트리의 일종이며 각 노드는 다음과 같은 특징을 가지고 있다.
* 리프 노드: 배열의 원소
* 단말 노드: 왼쪽 자식 노드와 오른쪽 자식 노드의 합
노드의 번호가 x일때 왼쪽 자식 노드는 x\*2,오른쪽 자식노드는 x\*2+1 이다.  
만약 배열의 크기가 7이라면 다음과 같은 형태의 세그먼트 트리가 형성된다.
![세그먼트_트리](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/image.png)  
빨간 색 노드는 단말노드, 하얀 색 노드는 리프 노드이다.
각 노드의 번호는 다음과 같다.
![세그먼트_트리_노드번호](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/image2.png)  

# 생성과정
만약 배열의 크기 N이 2의 n제곱 꼴이면 트리는 완전 이진 트리의 형태를 보인다. 이 때, 트리의 높이는 logN이다.  
따라서 필요한 세그먼트 트리의 배열 크기는 2\*N-1 이다. 
만약 N이 2의 n제곱 꼴이 아니라면 트리의 높이 H=\[logN\]이다.
따라서 필요한 노드의 크기는 2*(H+1)-1 이다.
트리는 다음과 같은 과정으로 만들 수 있다.
```
//SegmentTree[treeIndex]=PartialSum(begin,last)
function MakeSegmentTree(begin, last, node):
  if(begin==last):
      return SegmentTree[node]=array[begin]
   else:
    mid=(begin+last)/2
    return SegmentTree[node]=
      MakeSegmentTree(begin, mid, node*2)+MakeSegmentTree(mid+1,last,node*2+1)
```
만약 begin==last이라면 해당 노드는 리프노드이다. 해당 노드의 번호는 treeIndex이고 값은 배열의 원소를 가진다. 
treeIndex의 왼쪽 자식은 start부터 mid 까지의 합, 오른쪽 자식은 mid+1부터 last 까지의 합이다. 이를 가장 위에서부터  
재귀적으로 수행하여 트리를 만들면 된다.
# 합 찾기
위에서 본 트리에서 구간 \[2,4\]의 합을 찾아보자.  
start=2, end=5 라 해보자.
그리고 각 트리의 단말 노드의 구간합의 범위를 \[left, right\]라 하자.  
먼저 트리의 루트 부분은 구간 \[0,6\]이다.  
즉, 우리가 탐색할 구간이 단말 노드의 구간에 겹쳐 있다. 따라서 이를 좌우로 나누어 다시 탐색하여야 한다.
![세그먼트_트리_탐색1](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/Serch1.png)  
먼저 왼쪽 구간을 보자. 이 노드의 구간 역시 \[2,4\]과 겹쳐 있으니 다시 좌우로 나누어 탐색한다.  
![세그먼트_트리_탐색2](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/Serch2.png)  
이 순간, 왼쪽 구간 \[0,1\] 은 \[2,4\]와 겹쳐 있지 않으므로 탐색하지 않는다.  
오른쪽 구간 \[2,3\]은 \[2,4\]의 일부분이다. 따라서 오른쪽 트리에선 더 탐색할 필요가 없이 이 구간의 합을 반환한다.
![세그먼트_트리_탐색3](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/Serch3.png)  
이제 루트의 오른쪽 부분을 탐색한다.  
오른쪽 트리의 구간 \[4,6\]은 \[2,4\]와 겹쳐 있다. 따라서 다시 좌우로 나누어 탐색한다.
![세그먼트_트리_탐색4](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/Serch4.png)  
위의 과정을 똑같이 진행하게 되면 다음과 같은 탐색을 하게 된다.
![세그먼트_트리_탐색5](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/Serch.png)  
따라서 어느 구간이든 최악의 경우, 트리의 높이만큼 탐색을 하게 되므로 구간합을 구하는데 O(logN) 만큼의 시간이 소요된다. 

이는 다음과 같이 표현할 수 있다.
```
function Sum(left,right, start, end, node):
  if(start>right||end<left):  //현재 구간이 [left,right]이 [start,end] 에 포함되지 않으면
    return 0
  if(start<=left&&right<=end):  //현재 구간 [left,right]이 [start,end] 에 포함된다면
    return SegmentTree[node]
  mid=(left+right)/2
  return Sum(left,mid,start,end,node*2)+Sum(mid+1,right, start, end, node*2+1)
```
# 갱신
만약 a3이 갱신 되었다 가정해보자. 그렇다면 우린 트리내부에서 a3가 포함된 구간을 모두 갱신하면 된다.
![세그먼트_트리_갱신1](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermeditae/SegmentTree/Update1.png)  
이 경우, 트리의 높이만큼 탐색을 하므로 O(logN) 만큼의 시간이 걸린다.

```
function Update(left,right, index,node):
  if(right<index||left>index):
    return SegmentTree[node]
  if(left==right):
    return SegmentTree[node]=A[index]
  mid=(left+right)/2
  return SegmentTree[node]=Update(left,mid,index,node*2)+Update(mid+1,right,index,node*2+1)
