package ai.weak_4;

import java.util.Scanner;

public class Exam_03 {

	public static void main(String[] args) {
		// 무한루프를 이용해 정수를 입력받아 짝수인지 홀수인지 판별
		// 0을 입력하면 종료
		Scanner scan = new Scanner(System.in);
		while(true) {
			System.out.print("정수 입력:");
			int i = scan.nextInt();
			if(i==0) {
				System.out.println("종료");
				break;
			}
			else if(i%2 == 0) {
				System.out.println("짝수");
			}
			else {
				System.out.println("홀수");
			}
		}

	}

}
