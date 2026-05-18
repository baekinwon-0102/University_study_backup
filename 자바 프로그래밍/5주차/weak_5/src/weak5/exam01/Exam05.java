package weak5.exam01;

import java.util.ArrayList;
import java.util.Scanner;

public class Exam05 {

	public static void main(String[] args) {
		// 좋아하는 과일 5개를 입력받아 ArrayList 클래스를 사용해 저장
		// 과일 리스트 출력
		// 찾고싶은 과일이름 입력받아 몇번째 있는지 찾음
		// 그 요소에 다른 과일을 저장하고 출력
		
		Scanner scan = new Scanner(System.in);
		ArrayList<String> fruit = new ArrayList<String>();
		System.out.print("과일 5개 입력: ");
		for(int i = 0;i<5;i++)
			fruit.add(scan.next());
		for(String fr:fruit)
			System.out.print(fr+" ");
		System.out.print("\n 찾고싶은 과일입력: ");
		String fi = scan.next();
		System.out.println(fi+"은(는) "+(fruit.indexOf(fi)+1)+"번 째에 있습니다.");
		fruit.set(fruit.indexOf(fi), "딸기");
		for(String fr:fruit)
			System.out.print(fr+" ");
	}

}
