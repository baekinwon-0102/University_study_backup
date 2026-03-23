package ai.weak_3;

import java.util.Scanner;

public class Weak3_03 {

	public static void main(String[] args) {
		// 정수입력받아 1 one 2 two 3 three 4 four 5 five
		
		Scanner scan = new Scanner(System.in);
		
		System.out.print("정수 입력: ");
		int num = scan.nextInt();
		
		switch(num) {
		case 1,2:
			System.out.println("상위");
			break;
		case 3,4:
			System.out.println("중위");
			break;
		default:
			System.out.println("하위");
			break;
		}
	}

}
