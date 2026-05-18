package weak6.cla;

import java.util.Scanner;

// Student 정의
// 속성 : 학번 이름 나이
// 동작 : 홍길동(20251111)의 나이는 23세 입니다
// 학번 이름 나이 입력받아서 저장하기

class Student{
	int grade;
	String name;
	int age;
	public void print() {
		System.out.println(name+"("+grade+")"+"의 나이는"+age+"세 입니다.");
	}
}

public class Test01 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		Student st = new Student();
		System.out.print("이름: ");
		st.name = scan.next();
		System.out.print("학번: ");
		st.grade = scan.nextInt();
		System.out.print("나이: ");
		st.age = scan.nextInt();
		st.print();
	}

}
