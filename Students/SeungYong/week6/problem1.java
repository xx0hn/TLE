import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Main {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st;

		int N = Integer.parseInt(br.readLine());
		int[][] map = new int[N][3];

		for (int i = 0; i < N; i++) {
			st = new StringTokenizer(br.readLine());
			for (int j = 0; j < 3; j++) {
				map[i][j] = Integer.parseInt(st.nextToken());
			}
		}

		int[] max = new int[3];
		int[] min = new int[3];

		for (int i = 0; i < N; i++) {
			if (i == 0) {
				for (int j = 0; j < 3; j++) {
					max[j] = map[0][j];
					min[j] = map[0][j];
				}
			} else {
				int zeroValue = max[0], secondValue = max[2];
				max[0] = Math.max(max[0], max[1]) + map[i][0];
				max[2] = Math.max(max[1], max[2]) + map[i][2];
				max[1] = Math.max(Math.max(zeroValue, secondValue), max[1]) + map[i][1];

				int minZero = min[0], minSecond = min[2];
				min[0] = Math.min(min[0], min[1]) + map[i][0];
				min[2] = Math.min(min[1], min[2]) + map[i][2];
				min[1] = Math.min(Math.min(minZero, minSecond), min[1]) + map[i][1];
			}
		}
		System.out
				.println(Math.max(Math.max(max[0], max[1]), max[2]) + " " + Math.min(Math.min(min[0], min[1]), min[2]));
	}

}
