# 개요
세그먼트 트리는 배열의 구간 합을 구하고 변경하는 과정을 O(logN) 만큼의 시간으로 수행할 수 있다는 것 알았다.  
그러나 세그먼트 트리는 N이 커진다면 트리는 만드는데 사용할 메모리가 매우 커진다.  
(세그먼트 트리를 만드는데 필요한 메모리의 크기는 2^(\[logN\]) 이다.)
이런 문제점을 보완하기 위해선 Fenwick Tree를 소개한다.
# 펜윅 트리
펜윅 트리는 이진수를 이용해 만드는 트리로 BIT(Binary Indexed Tree) 라고도 부른다.  
펜윅 트리의 노드는 다음 그림에서 파란색 노드에 해당하고 노드들의 구간합은 다음과 같이 표현된다.  
  
![펜윅트리_범위구간](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermediate/FenwickTree/Range.png)  
  
펜윅 트리의 노드번호는 다음과 같고 노드들의 개수는 트리를 만들기 위해 사용한 배열의 길이와 같다.
  
![펜윅트리_노드](https://raw.githubusercontent.com/leeminseokdankook/TLE/main/Intermediate/FenwickTree/tree_index.png)  

# 성질

위의 펜윅 트리에서 8번 노드 FenwickTree\[8\]=FenwickTree\[1000\]=A\[1\]+A\[2\]+A\[4\]+A\[8\]=A\[0001\]+A\[0010\]+A\[0100\]+A\[1000\] 이다.  
6번 노드  FenwickTree\[6\]=FenwickTree\[0110\]=A\[5\]+A\[6\]=A\[0101\]+A\[0110\] 이다.  
즉, F(x) = (x를 이진수로 표현했을 때, 마지막에 위치한 1의 위치) 라 하면  
펜윅 트리의 노드 번호를 i 라 두면 해당 노드의 구간은 \[i-(1<<F(i))+1, i\]이다. 

# 구현및 갱신
BIT는 이름처럼 이진수를 이용하여 만들 수 있다.  
펜윅 트리의 노드 번호를 i 라 두면 해당 노드의 구간은 \[i-(1<<F(i))+1, i\]이다. 
따라서 배열의 i번째 원소 v를 펜윅 트리에 넣어 갱신을 진행하면 다음과 같은 과정을 수행한다.  
```
1. 펜윅 트리의 i번째 노드에 배열의 v를 더한다.
2. i에 (1<<F(i))를 더한다.
3. i가 배열의 크기를 넘지 않으면 1로 돌아간다.
```
그렇다면 (1<<F(i)) 를 어떻게 구할 수 있을까?
무작정 구한다면 1번째 비트부터 검사하며 1이 나오는 위치를 찾으면 된다.  
여기서 i와 -i의 관계를 보자.  
-i는 i의 비트를 모두 뒤집은 다음 1비트를 더하면 나온다. i의 비트를 모두 뒤집는다면 F(i)보다 뒤에 있던 0부분은 모두 1이 된다.  
여기에 1비트를 더하면 F(i)==F(-i)라 할 수 있다. 따라서 (1<<F(i)) 는 (i&(-i)) 와 같음을 알 수 있다.  
이를 코드로 표현하면 다음과 같다.  
```
function Update(v, i, array_size):
  node=i
  while(node<=array_size):
    FenwickTree[node]+=v
    node+=(node&(-node))
```
  
Update 갱신함수의 시간복잡도는 O(logN), 이를 총 N번 반복하므로 펜윅트리를 구성하는데 걸리는 시간은 O(NlogN) 이다.

# 구간 합 구하기
세그먼트 트리의 경우, 시작지점과 마지막 지점을 알면 트리를 한번만 순회하면 구간 합을 알 수 있다. 그러나 펜윅트리의 경우, 한 번의 탐색으로 구간 합을 알 수 있는 경우는 특수한 케이스밖에 없다.그러나 펜윅 트리의 성질을 보자.  
펜윅 트리의 노드번호 i의 구간 합은 \[i-F(i)+1, i\] 이다. 이 때 다음과 같은 과정을 반복하게 되면
```
function Sum(i):
  node=i
  sum=0
  while(node>0):
    sum+=FenwickTree[node]
    node-=(node&(-node))
  return sum
```
sum 에는 구간 \[1,i\]의 합이 저장된다. 따라서 펜윅트리에서 구간\[start, end\]의 합을 구하려면 Sum(end)-Sum(start-1)이 된다.