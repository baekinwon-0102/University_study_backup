package day11.study;
// 멤버변수: color
// 메서드: colorPoint()red(10,10)
public class ColorPoint extends Point{
	// 1. 상속받은 부모클래스가 생성자로 정의되어있으면 반드시 서브클래스도 생성자로 정의(필수)
	// 2. 반드시 부모클래스의 생성자를 호출
	private String color;
	public ColorPoint(int x, int y, String color) {
		super(x,y);
		this.color = color;
	}
	public void colorPoint() {
		System.out.print(color);
		super.showPoint();
	}
}
