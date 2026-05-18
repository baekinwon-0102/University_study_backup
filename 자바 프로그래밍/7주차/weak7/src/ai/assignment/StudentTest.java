package ai.assignment;

import java.util.ArrayList;
import java.util.Scanner;

public class StudentTest {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		ArrayList<Student> st = new ArrayList<Student>();
		
		for(int i = 0;i<3;i++) {
			System.out.println("==="+(i+1)+"번 학생 정보 ===");
			System.out.print("이름 입력:");
			String name = scan.next();
			System.out.print("국어 점수:");
			int kor = scan.nextInt();
			System.out.print("영어 점수:");
			int eng = scan.nextInt();
			System.out.print("수학 점수:");
			int math = scan.nextInt();
			st.add(new Student(name,kor,eng,math));
		}
		System.out.println("====결과====");
		for(Student li:st) {
			li.avg = (double)(li.kor+li.eng+li.math)/3.0;
			if(li.avg>=90) {
				li.grade="A";
			}else if(li.avg>=80) {
				li.grade="B";
			}else if(li.avg>=70) {
				li.grade="C";
			}else if(li.avg>=60) {
				li.grade="D";
			}else {
				li.grade="F";
			}
			System.out.println(li.toString());
		}
	}

}
