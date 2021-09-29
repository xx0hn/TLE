
import java.util.*;

public class problem3{
	static Scanner sc = new Scanner(System.in);
	public static void main(String[] args) {
		int n = sc.nextInt();
		int cnt = 0;
		int i;
		
		for(i = 0; cnt < n; i++) {
			if(decNum(i)) {
				cnt++;
			}
		}
		System.out.println(i);
		
		sc.close();
	}
	
	static boolean decNum(int n) {
		int size = findNumMaxSize(n);
		
		while(size >= 10) {
			int frontNum = n/size;
			n -= (frontNum * size);
			size /= 10;
			int backNum = n/size;
			if(frontNum <= backNum) {
				return false;
				
			}
		}
		return true;
	}
	
	static int findNumMaxSize(int n) {
		int size= 10;
		
		while(true) {
			if(n / size == 0) {
				break;
			}
			size *= 10;
		}
		return size / 10;
	}
}