package week12.sh;

abstract class Shape{
	// 1. 추상클래스는 자기자신은 객체화할 수 없는 추상화된 클래스
	// 2. 상속받은 서브클래스로 부터 객체화해 핸들링
	protected String name;
	public abstract void getArea();
}
class Circle extends Shape{
	// 추상클래스를 상속받은 서브클래스는 반드시 추상클래스의 추상메서드를 오버라이딩
	
	private int r;
	public Circle(String name, int r) {
		super.name = name;
		this.r = r;
	}
	
	@Override
	public void getArea() {
		System.out.println(name+"의 면적은 = "+(r*r*3.14));
	}	
}

class Square extends Shape{
	private int x,y;
	public Square(String name, int x, int y) {
		super.name = name;
		this.x = x;
		this.y = y;
	}
	
	@Override
	public void getArea() {
		System.out.println(name+"의 넓이는 = "+(x*y));
	}
}

class Triangle extends Shape{
	private int x,y;
	public Triangle(String name, int x, int y) {
		super.name = name;
		this.x = x;
		this.y = y;
	}
	
	@Override
	public void getArea() {
		System.out.println(name+"의 넓이는 = "+(x*y/2));
	}
}

public class ShapeTest {

	public static void main(String[] args) {
		Shape s1 = new Circle("원",10);
		Shape s2 = new Square("사각형",4,10);
		Shape s3 = new Triangle("삼각형",5,3);
		Shape[] s = {s1,s2,s3};
		
		for(Shape li:s) {
			li.getArea();
		}

	}

}
