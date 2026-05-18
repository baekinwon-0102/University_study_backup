package ai.cir;

public class Exam02 {

	public static void main(String[] args) {
		// 반지름이 1부터 5까지 가진 객체를 생성해
		// 원의 면적을 출력하는 프로그램 작성
		
		Circle[] c = new Circle[5];
		
		for(int i = 0;i<c.length;i++) {
			c[i] = new Circle(i+1);
		}
		
		for(Circle cs:c) {
			System.out.print((int)cs.getRe()+" ");
		}
	}

}
