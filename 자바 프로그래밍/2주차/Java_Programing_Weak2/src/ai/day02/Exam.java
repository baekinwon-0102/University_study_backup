package ai.day02;

import java.util.Scanner;

public class Exam {

	public static void main(String[] args) {
		//두 개의 정수를 입력받아 더한결과, 곱한결과를 출력
		Scanner scan = new Scanner(System.in);
		
		System.out.print("두 개의 정수를 공백을 넣어 입력하시오: ");
		
		int a = scan.nextInt();
		int b = scan.nextInt();
		
		System.out.println(a+" + "+b+" = "+(a+b));
		System.out.println(a+" X "+b+" = "+(a*b));
	}

}
