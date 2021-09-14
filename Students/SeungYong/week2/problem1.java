import java.io.*;
import java.util.*;

public class problem1 {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	static StringTokenizer st;
	static int N, M;
	static int[] arr;
	static int difNumCnt = 0;
	static int[] temp;
	static boolean[][] check;

	public static void main(String[] args) throws IOException {
		st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		temp = new int[M];
		st = new StringTokenizer(br.readLine());
		arr = new int[N];
		for (int i = 0; i < arr.length; i++) {
			arr[i] = Integer.parseInt(st.nextToken());
		}
		arr = checkNum();
		Arrays.sort(arr);
		// 몇번째 자리의 몇번째 수
		check = new boolean[M][difNumCnt];

		backTracking(0);
		bw.flush();
		bw.close();
	}

	static void backTracking(int size) throws IOException {
		if (size == M) {
			for (int temp : temp) {
				bw.append(temp + " ");
			}
			bw.append("\n");
		} else {
			for (int i = 0; i < difNumCnt; i++) {
				if (!check[size][i]) {
					temp[size] = arr[i];
					check[size][i] = true;
					backTracking(size + 1);
					check[size][i] = false;
				}

			}
		}
	}

	// 수열에 사용할 수 있는 수 찾기
	static int[] checkNum() {
		ArrayList<Integer> list = new ArrayList<>();
		boolean[] check = new boolean[10001];
		for (int i = 0; i < arr.length; i++) {
			if (!check[arr[i]]) {
				list.add(arr[i]);
				check[arr[i]] = true;
				difNumCnt++;
			}
		}
		int[] returnArr = new int[difNumCnt];
		for (int i = 0; i < difNumCnt; i++) {
			returnArr[i] = list.get(i);
		}
		return returnArr;
	}
}