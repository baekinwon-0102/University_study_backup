package weak6.cla;

class Circle{
	//1. 속성: 멤버변수, 2. 동작: 메서드(함수), 3. 생성자: 초기화가 목적인 특수한 메서드 형태
	// 생성자: 초기화가 목적인 특수한 메서드:
	// 1. 클래스 이름과 동일, 2. 반환상태 X void X
	// 3. 똑같은 이름의 생성자 중복 정의 == 매개변수의 개수나 타입이 달라야 함
	// == 생성자의 오버로딩(다형성) ==
	// 4. 객체를 생성 시 단 하나의 생성자만 호출
	// 5. 단 하나의 생성자라도 정의되어있으면 디폴트 생성자 호출
	// 반지름 이름을 정의하고 원의 면적을 반환해주는 클래스 정의
	double r; // 멤버변수
	String name;
	//이름만 초기화하는 생성자
	public Circle(String n) {
		name = n;
	}
	
	public Circle(double ra) {
		r = ra;
	}
	
	// 모든 값을 초기화하는 생성자 정의
	public Circle(String n, double ra) {
		name = n;
		r = ra;
	}
	
	// 원의 면적을 반환하는 메서드 정의
	public double getArea() {
		return r*r*3.14;
	}
	// 출력하는 메서드 정의
	public void returnR() {
		System.out.println(name+"의 면적은 = "+getArea());
	}
}

public class CircleTest {

	public static void main(String[] args) {
		Circle c1 = new Circle("피자",5.3); // 객체 생성
		c1.returnR();
		Circle c2 = new Circle("야구공",2.0);
		Circle c3 = new Circle("농구공");
		Circle c4 = new Circle(3.3);
		c2.returnR();
		c3.returnR();
		c4.returnR();
		// 생성자를 초기화하지 않은 값은
		// 1. 정수: 0, 2. 문자: null. 3. 실수: 0.0으로 초기화
	}

}
