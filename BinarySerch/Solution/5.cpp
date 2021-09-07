#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int* stay, N, M, L,left, right;
	cin >> N >> M>>L;
	stay = new int[N + 2];
	stay[0] = 0;
	for (int i = 1; i <= N; i++) {
		cin >> stay[i];
	}
	stay[N+1] = L;
	sort(stay+1, stay + N + 1);
	left = 0; right = L - 1;
	while (left <= right) {
		int mid = (left + right) >> 1, cnt=0;
		for (int i = 0; i <= N; i++) {
			if (stay[i + 1] - stay[i] > mid) {
				cnt += (stay[i + 1] - stay[i] - 1) / mid;
			}
		}
		if (cnt > M) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	cout << left;
	delete[] stay;
	return 0;
}
