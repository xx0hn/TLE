import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class problem1 {

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		int T = Integer.parseInt(br.readLine());

		for (int i = 0; i < T; i++) {
			int n = Integer.parseInt(br.readLine());
			if (primeCheck(n)) {
				int lowerPrime = lowerPrime(n);
				int upperPrime = upperPrime(n);
				int length = upperPrime - lowerPrime;
				bw.append(length + "\n");
			} else {
				bw.append("0\n");
			}
		}
		bw.flush();
		bw.close();
	}

	// 소수일 시 falseqksghks
	static boolean primeCheck(int n) {
		for (int i = 2; i * i <= n; i++) {
			if (n % i == 0)
				return true;
		}
		return false;
	}

	static int lowerPrime(int n) {
		while (true) {
			n--;
			if (primeCheck(n) == false)
				break;
		}
		return n;
	}

	static int upperPrime(int n) {
		while (true) {
			n++;
			if (primeCheck(n) == false)
				break;
		}
		return n;
	}
}
