package ai.weak_3;

import java.util.Scanner;

public class Test_04 {

	public static void main(String[] args) {
		// 월을 입력받아 그 월의 일수를 계산
		
		Scanner scan = new Scanner(System.in);
		System.out.print("월을 입력하시오: ");
		int month = scan.nextInt();
		int day = 0;
		switch(month) {
		case 2:
			day =28;
			break;
		case 4,6,9,11:
			day = 30;
		    break;
		case 1,3,5,7,8,10,12:
			day = 31;
		    break;
		default:
			System.out.println("wrong input");
		}
		System.out.println(month+"월은 "+day+"일입니다.");
	}

}
