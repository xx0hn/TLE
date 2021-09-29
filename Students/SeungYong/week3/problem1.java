
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;

public class problem1 {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	static StringTokenizer st;
	static int N, Q;
	static ArrayList<Node>[] list;
	static int cnt;
	static boolean[] visited;

	static class Node {
		private int video, usado;

		Node(int video, int usado) {
			this.video = video;
			this.usado = usado;
		}
	}

	public static void main(String[] args) throws IOException {
		input();

		for (int i = 0; i < Q; i++) {
			st = new StringTokenizer(br.readLine());
			int k = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken());

			cnt = 0;
			visited = new boolean[N + 1];

			bfs(k, v);
			System.out.println(cnt);
		}
	}

	static void input() throws IOException {
		st = new StringTokenizer(br.readLine());
		N = Integer.parseInt(st.nextToken());
		Q = Integer.parseInt(st.nextToken());

		list = new ArrayList[N + 1];
		for (int i = 0; i < N + 1; i++) {
			list[i] = new ArrayList<>();
		}

		for (int i = 0; i < N - 1; i++) {
			st = new StringTokenizer(br.readLine());
			int videoA = Integer.parseInt(st.nextToken());
			int videoB = Integer.parseInt(st.nextToken());
			int usado = Integer.parseInt(st.nextToken());
			list[videoA].add(new Node(videoB, usado));
			list[videoB].add(new Node(videoA, usado));
		}
	}

	static void bfs(int k, int v) {
		Queue<Integer> queue = new LinkedList<>();
		queue.offer(v);
		visited[v] = true;
		while (!queue.isEmpty()) {
			int video = queue.poll();

			for (int i = 0; i < list[video].size(); i++) {
				int nextVideo = list[video].get(i).video;
				int usado = list[video].get(i).usado;
				if (!visited[nextVideo] && usado >= k) {
					cnt++;
					queue.offer(nextVideo);
					visited[nextVideo] = true;
				}
			}
		}
	}

}