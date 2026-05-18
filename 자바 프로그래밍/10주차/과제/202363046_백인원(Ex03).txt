package weak10.exam01;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Ex03 {

	public static void main(String[] args) {
		// 3개의 정수 입력해서 그 정수의 합 출력
		// 정수가 아닌 값을 입력시 잘못된 값을 버리고 다시 입력받아 합 출력
		int sum = 0,n;
		Scanner scan = new Scanner(System.in);
		System.out.println("3개의 정수입력");
		for(int i=1;i<=3;i++) {
			System.out.print(i+"번째 정수 입력: ");
			try {
				n = scan.nextInt();
			} catch (InputMismatchException e) {
				System.out.println("정수가 아닙니다. 다시 입력하세요.");
				scan.next(); //잘못입력된 값을 비우기 (초기화)
				i--;
				continue;
			}
			sum += n;
		}
		System.out.println("3정수의 합은 = "+sum);
		

	}

}
