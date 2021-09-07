package Solution;
import java.io.*;
import java.util.*;

public class problem3 {
    public static void main(String[] args) throws IOException {
		// input
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		int n = Integer.parseInt(br.readLine());
		int[] A = new int[n];
		A = makeArr(A, br.readLine());
		int m = Integer.parseInt(br.readLine());
		int[] B = new int[m];
		B = makeArr(B, br.readLine());

		// make list
		ArrayList<Integer> a = new ArrayList<>();
		ArrayList<Integer> b = new ArrayList<>();
		a = makeList(a, A);
		b = makeList(b, B);

		Collections.sort(a);
		Collections.sort(b);

		for (int temp : a) {
			System.out.print(temp + " ");
		}
		System.out.println();
		for (int temp : b) {
			System.out.print(temp + " ");
		}
		System.out.println();

		// find answer
		int pa = 0;
		int pb = b.size() - 1;
		int aSize = a.size();
		int sum;
		long cnt = 0;
		while (pa < aSize && pb >= 0) {
			sum = a.get(pa) + b.get(pb);
			if (sum == T) {
				int valueA = a.get(pa);
				int valueB = b.get(pb);
				long lengthA = 1;
				long lengthB = 1;
				pa++;
				pb--;

				while (pa < aSize && a.get(pa) == valueA) {
					pa++;
					lengthA++;
				}
				while (pb >= 0 && b.get(pb) == valueB) {
					pb--;
					lengthB++;
				}
				cnt += (lengthA * lengthB);
			} else if (sum > T) {
				pb--;
			} else if (sum < T) {
				pa++;
			}
		}
		System.out.println(cnt);
	}

	static int[] makeArr(int[] arr, String s) {
		StringTokenizer st = new StringTokenizer(s);
		for (int i = 0; i < arr.length; i++) {
			arr[i] = Integer.parseInt(st.nextToken());
		}
		return arr;
	}

	static ArrayList<Integer> makeList(ArrayList<Integer> list, int[] arr) {
		int sum = 0;
		for (int i = 0; i < arr.length; i++) {
			sum = arr[i];
			list.add(sum);
			for (int j = i + 1; j < arr.length; j++) {
				sum += arr[j];
				list.add(sum);
			}
		}
		return list;
	}
}
