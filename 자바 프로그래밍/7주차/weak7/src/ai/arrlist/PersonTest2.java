package ai.arrlist;

import java.util.ArrayList;
import java.util.Scanner;

public class PersonTest2 {

	public static void main(String[] args) {
		// ArrayList 클래스를 사용해 3명 친구의 이름과 전화번호를 입력받고 출력하기
		Scanner sc = new Scanner(System.in);
		
		ArrayList<Person> p = new ArrayList<Person>();
		
		for(int i = 0;i<3;i++) {
			System.out.print("이름: ");
			String name = sc.next();
			System.out.print("전화번호: ");
			String tel = sc.next();
			p.add(new Person(name,tel));
		}
		
		for(Person li:p) {
			System.out.println(li.toString());
		}
	}

}
