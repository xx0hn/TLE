import java.io.*;
import java.util.*;

public class problem2 {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static StringTokenizer st;
	static int n;
	static int[] arr;
	static int plus, minus, mul, div;
	static int[] math;
	static int min = Integer.MAX_VALUE;
	static int max = Integer.MIN_VALUE;
	static boolean[][] check;

	public static void main(String[] args) throws IOException {
		input();
		backTracking(0, arr[0]);
		System.out.println(max);
		System.out.println(min);
	}

	static void backTracking(int size, int value) {
		if (size == n - 1) {
			min = value < min ? value : min;
			max = value > max ? value : max;
			return;
		} else {
			for (int i = 0; i < 4; i++) {
				if (!check[size][i] && math[i] > 0) {
					check[size][i] = true;
					math[i]--;
					int beforeValue = value;
					switch (i) {
					case 0:
						value += arr[size + 1];
						break;
					case 1:
						value -= arr[size + 1];
						break;
					case 2:
						value *= arr[size + 1];
						break;
					case 3:
						value /= arr[size + 1];
						break;
					}
					backTracking(size + 1, value);
					value = beforeValue;
					check[size][i] = false;
					math[i]++;
				}
			}
		}

	}

	static void input() throws IOException {
		n = Integer.parseInt(br.readLine());
		st = new StringTokenizer(br.readLine());
		arr = new int[n];
		for (int i = 0; i < n; i++) {
			arr[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(br.readLine());
		math = new int[4];
		for (int i = 0; i < 4; i++) {
			math[i] = Integer.parseInt(st.nextToken());
		}
		check = new boolean[n - 1][4];
	}
}