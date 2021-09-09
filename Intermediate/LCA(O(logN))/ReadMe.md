# LCA란?
LCA(Lowest Common Ancestor)은 영문대로 최소 공통 조상을 의미하며 임의의 두 정점에서 자신의 부모 정점으로 거슬러 올라가며 방문할 때, 처음으로 두 번 방문하게 되는 정점을 의미한다.  
  
1번 노드라 루트인 아래의 트리를 보자.  
![트리](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermediate/LCA(O(logN))/Tree.png)  
  
이 트리에서 15번 정점과 17번 정점의 LCA는 3번이 된다.  
![트리](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermediate/LCA(O(logN))/LCA_1.png)  


# LCA 구현
처음 소개할 때 정의한 개념의 방법을 조금 개선해보자. 트리 내부의 임의의 두 정점 u, v에 대해서 각 정점의 깊이를 d(u), d(v)라 하자.  
만약 d(u)와 d(v) 가 같다면 두 정점은 서로 부모 정점으로 이동하며 이 과정을 서로가 같은 정점일 때까지 반복하면 된다.
```
while(u!=v):
    u=parent(u)
    v=parent(v)
```
그렇다면 두 정점의 깊이가 다르다면 어떻게 할까? 이는 매우 간단하다. 더 깊은 정점을 덜 깊은 정점의 깊이까지 올리면 된다.  
```
if(d(u)<d(v)):
    swap(u,v)
while(d(u)!=d(v)):
    u=parent(u)
```
이를 합치면 임의의 두 정점 u,v의 LCA를 찾는 방법은 다음과 같다.
```
function find_LCA(u,v):
    if(d(u)<d(v)):
        swap(u,v)
    while(d(u)!=d(v)):
        u=parent(u)
    while(u!=v):
        u=parent(u)
        v=parent(v)
    return u
```
이 알고리즘은 최악의 경우, 트리의 높이(H) 만큼의 시간 복잡도 *O(H)* 를 가진다. 만약 해당 트리가 편향된 트리라면 H=N이 된다. 따라서 해당 알고리즘은 *O(N)* 의 시간복잡도를 가진다. 이를 개선시킬 방법은 무엇이 있을까?

# 개선
DP 기법을 이용해보자.
위의 알고리즘에서 정의한 parent 를 이용해 새로운 new_parent를 정의해보겠다
* p(0,v)=v
* p(k,v)=v (v is root of tree)
* p(k,v)=p(k-1,parent(v))
* new_parent(0,v)=p(1,v)
* new_parent(i,v)=new_parent(i-1, new_parent(i-1,v))  

i=1 이면
```
new_parent(1,v) = new_parent(0,new_parent(0,v))  
                =p(2,v)
```
이다. 따라서 new_parent(1,v)는 v의 2번째 부모가 된다.  
i=2 이면
```
new_parent(2,v) = new_parent(1,new_parent(1,v))  
                = new_parent(1,p(2,v))) 
                = p(2,p(2,v))
                = p(4,v)
```
이다. 따라서 new_parent(2,v)는 v의 4번째 부모가 된다.
i=3 이면 
```
new_parent(3,v) = new_parent(2,new_parent(2,v))
                = new_parent(2,p(4,v))
                = new_parent(1,new_parent(1,p(4,v)))
                = new_parent(1,p(2,(4,v)))
                = new_parent(1,p(6,v))
                = p(2,p(6,v))
                = p(8,v)
```
이다. 따라서 new_parent(3,v) 는 v의 8번째 부모가 된다. 이를 일반화하면 new_parent(i,v) = p(2^i, v) 가 된다.  
이를 LCA 를 찾을 때 써보자.  
편의상, 임의의 두 정점 u,v에서 d(u)==d(v) 라 하자. 이때 new_parent(i,u)==new_parent(i,v) 라면 p(2^i, u)와 p(2^i, v)가 같음을 의미한다. 이는 u와 v의 LCA에 해당하는 정점의 깊이는 두 정점의 2^i번째 부모보다 더 깊거나 같은 곳에 있음을 의미한다.  
이를 반대로 생각하면 p(2^i, u)와 p(2^i, v)가 다르다면 LCA는 두 정점의 2^i번째 부모보다 얕은 곳에 있다는 것이다. 따라서 u,v를 갱신한다.
이를 i가 감소하는 방향으로 진행하면 최종적으로 p(1,v)==p(1,u) 가 된다. (v!=u)
```
과정 2
for(i=max_i, i>=0;--i):
    if(new_parent(i,u)!=new_parent(i,v)):
        u=new_parent(i,u)
        v=new_parent(i,v)
    return p(1,v)
```
max_i는 추후 설명하겠다.  
그렇다면 d(u)와 d(v) 가 다르면 어떻게 될까? 두 정점의 높이를 맞추기 위해 새로 정의한 new_parent를 이용하면 된다. 이 떄, new_parent(i,v)=p(2^i, v) 인 꼴을 이용하면 두 높이의 차이의 비트를 이용하면 된다.
```
과정 1
distnace=d(u)-d(v) (d(u)>=d(v))
for(i=0;distance!=0;--i):
    if((distance & 1) == 1):
        //u의 2^i번째 부모로 갱신한다.
        //원래의 distance에 (i+1)번째 비트가 존재했음
        u=new_parent(i,u)
    distance=distance>>1 //1비트씩 오른쪽으로 당김
```
그렇다면 max_i는 어떻게 될까? 트리의 높이를 H라 하면 가장 깊은 곳에 있는 정점 v에서 p(2^k, v) == (트리의 루트 정점) 을 만족하는 최소 k값이 max_i 라면 모든 정점 u 에 대하여 new_parent(i,u) (0<=i<=max_i) 에 대하며 정의할 수 있다. 따라서 max_i=\[logH\] 이다.
그렇다면 위의 알고리즘의 시간 복잡도는 어떻게 될까? 모든 정점 u 에 대하여 new_parent(i,u) (0<=i<=max_i)를 저장하는 과정을 제외하고 1번 과정의 경우, distance의 모든 비트를 검사하므로 과정 1은 O(log\[H\]) 만큼의 시간이 걸린다. 과정 2의 경우, max_i=\[logH\] 이므로 O(log\[H\]) 만큼의 시간이 걸린다. 따라서 총 시간 복잡도는 O(logH)+O(logH)=O(logH)이다. 이 때 편향 트리의 경우, H=N이므로 O(logN)이 된다위 과정을 합치면 다음과 같다.
```
function find_LCA(u,v):
    if(d(u)<d(v)):
        swap(u,v)
    distance=d(u)-d(v)
    for(i=0;distance!=0;++i):
        if((distance & 1) == 1):
            u=new_parent(i,u)
        distance=distance>>1
    //u와 v가 같다면 더 탐색을 해선 안된다.
    if(u==v):
        return u
    for(i=max_i;i>=0;--i):
        if(new_parent(i,u)!=new_parent(i,v)):
            u=new_parent(i,u)
            v=new_parent(i,v)
    return p(1,v)
```
