package ai.weak_4;

import java.util.Scanner;

public class Exam_01 {

	public static void main(String[] args) {
		// 단을 입력받아 그 단의 구구단 출력
		Scanner scan = new Scanner(System.in);
		System.out.print("출력할 단을 입력하시오: ");
		int dan = scan.nextInt();
		for(int i = 1;i<=9;i++) {
			System.out.println(dan+" X "+i+" = "+(dan*i));
		}
		scan.close();
	}

}
