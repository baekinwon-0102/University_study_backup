package weak13.exam01;

public interface Calc {
	// 서로 다른 장치들의 연결되어 상호 데이터를 주고받는 규칙
	// 다른 클래스로부터 인터페이스에 선언된 메서드를 구현
	// == 상속받은 서브클래스가 반드시 선언된 메서드를 오버라이딩 ==
	// 1. 자기자신은 객체화할 수 없다
	// 2. 일반멤버변수 메서드 생성자 올 수 없다
	// 3. 인터페이스는 선언된 메서드로 구성
	// -- 예외1: 상수값, static 멤버변수(하나만)
	// -- 예외2: static 메서드, default 메서드
	final double pi = 3.14;
	final int ERROR = -9999;
	
	public int add(int a, int b);
	public int sub(int a, int b);
	public int times(int a, int b);
	public int divide(int a, int b);
	
	default public void print() {
		System.out.println("=====정수계산기입니다.======");
	}
	
	public static int total(int[] arr) {
		int sum =0;
		for(int li:arr) {
			sum+=li;
		}
		return sum;
	}
}
