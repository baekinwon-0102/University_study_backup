package weak6.cla;

class Math{
	// 메서드의 중복정의 == 메서드의 오버로딩(다형성)
	// 규칙: 똑같은 이름의 메서드를 중복 정의가 가능하나 매개변수의 개수나 타입이 달라야 함
	public int getSum(int x, int y) {
		return x+y;
	}
	
	public int getSum(int x, int y,int z) { 
		return x+y+z;
	}
	
	public double getSum(double x, double y) {
		return x+y;
	}
	public int getSum(int x) {
		return x+x;
	}
	
}

public class MathTest {

	public static void main(String[] args) {
		Math m1 = new Math();
		System.out.println(m1.getSum(10));
		System.out.println(m1.getSum(10,20));
		System.out.println(m1.getSum(10.5,2.5));
		System.out.println(m1.getSum(10,20,30));
	}

}
