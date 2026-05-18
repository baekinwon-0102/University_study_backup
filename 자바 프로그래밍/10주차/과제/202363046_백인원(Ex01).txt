package weak10.exam01;

import java.util.Scanner;

public class Ex01 {

	public static void main(String[] args) {
		// 두 정수를 입력받아 나누기 연산
		int num1,num2,result;
		Scanner scan = new Scanner(System.in);
		
		System.out.print("피젯수 입력: ");
		num1 = scan.nextInt();
		System.out.print("젯수 입력: ");
		num2 = scan.nextInt();
		
		try {
			result = num1/num2;
			System.out.println("두정수의 나눈결과: "+result);
		}catch(ArithmeticException e) {
			System.out.println("0으로 나눌 수 없습니다.");
		}finally {
			System.out.println("프로그램 종료");
		}
	}

}
