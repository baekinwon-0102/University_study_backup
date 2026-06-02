package weak13.exam01;

public class Circle implements Printable, Draw{

	@Override
	public void draw() {
		System.out.println("화면에 원을 그려 출력합니다.");
	}

	@Override
	public void print() {
		System.out.println("프린터로 원을 출력합니다.");
	}
	
}
