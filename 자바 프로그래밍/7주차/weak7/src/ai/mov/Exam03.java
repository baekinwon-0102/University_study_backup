package ai.mov;

import java.util.Scanner;

public class Exam03 {

	public static void main(String[] args) {
		// Movie 클래스의 객체배열 3개를 선언하고
		// 영화제목과 감독을 입력받아 객체를 생성하고 출력
		Scanner scan = new Scanner(System.in);
		
		Movie[] m = new Movie[3]; //객체선언
		
		for(int i =0;i<m.length;i++) {
			System.out.print("영화 제목: ");
			String title = scan.next();
			System.out.print("감독: ");
			String author = scan.next();
			m[i] = new Movie(title,author); //객체생성
		}
		
		for(Movie li:m) {
			System.out.println(li.toString());
		}
	}

}
