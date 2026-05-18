package ai.weak_4;

import java.util.Scanner;

public class Exam_02 {

	public static void main(String[] args) {
		// 0이 아닐때까지 정수를 입력받아 그 정수의 합계를 출력
		// 몇 개의 정수가 입력되고 합계는 얼마인지 출력하시오
		Scanner scan = new Scanner(System.in);
		
		int sum = 0,inp = 0;
		System.out.print("정수를 입력하시오: ");
		int i = scan.nextInt();
		while(i!=0) {
			sum +=i;
			System.out.print("정수를 입력하시오: ");
			i = scan.nextInt();
			inp++;
		}
		System.out.println("정수의 개수: "+inp+" 정수의 합: "+sum);
	}

}
