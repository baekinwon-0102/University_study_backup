package week12.day19;

public abstract class Animal {
	public void eat() {
		System.out.println("냠냠");
	}
	// 추상메서드: 아무것도 정의되지 않은 선언된 메서드
	// 1. 일반클래스에 정의할 수 없음 == 반드시 추상클래스
	// 2. 추상클래스를 상속받은 서브클래스는 반드시 추상메서드를 구현해야 함(오버라이딩)
	public abstract void cry();
}
