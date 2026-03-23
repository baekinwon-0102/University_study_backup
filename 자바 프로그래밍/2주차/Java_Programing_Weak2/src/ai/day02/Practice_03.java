package ai.day02;
import java.util.Scanner;

public class Practice_03 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		System.out.println("당신의 이름[1], 나이[2], 키[3]를 입력하시오: ");

		String name = scan.next();
		int age = scan.nextInt();
		double height = scan.nextDouble();
		
		System.out.println(name+"의 나이는 "+age+"세"+" 키는 "+height+"입니다.");
	}

}
