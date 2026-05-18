package ai.weak_3;

import java.util.Scanner;

public class Test_05 {

	public static void main(String[] args) {
		//세개의 정수를 입력받아 가장 큰 수 출력
		
		Scanner scan = new Scanner(System.in);
		
		System.out.print("서로 다른 정수 3개 입력: ");
		int num1 = scan.nextInt();
		int num2 = scan.nextInt();
		int num3 = scan.nextInt();
		int max = 0;
		if(num1 > num2) {
			max = (num1>num3)?num1:num3;
		}
		else {
			max = (num2>num3)?num2:num3;
		}
		System.out.println("가장 큰 수는 "+max+"입니다.");
	}

}
