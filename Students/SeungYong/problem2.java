package Solution;
import java.io.*;
import java.util.*;

public class problem2 {
    public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine());

		int n = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int lev[] = new int[n];
		for (int i = 0; i < n; i++) {
			lev[i] = Integer.parseInt(br.readLine());
		}
		System.out.println(findMinLev(lev, k, n));
	}

	static int findMinLev(int[] lev, int k, int n) {
		Arrays.sort(lev);
		int i = 1;
		while (k > 0) {
			if (i < n && lev[0] == lev[i]) {
				do {
					i++;
				}
				while(i < n && lev[i] <= lev[0]);

			}
			if (k - i < 0) {
				break;
			}
			k -= i;
			lev[0]++;
		}
		return lev[0];
	}

}
