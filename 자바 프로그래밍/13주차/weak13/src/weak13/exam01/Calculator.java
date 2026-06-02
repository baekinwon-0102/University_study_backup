package weak13.exam01;
// 인터페이스 상속받는 명령어: implements
// 인터페이스 상속받은 서브클래스는 반드시 인터페이스의
// 선언된 메서드를 오버라이딩 해야 함
public class Calculator implements Calc{

	@Override
	public int add(int a, int b) {
		// TODO Auto-generated method stub
		return a+b;
	}

	@Override
	public int sub(int a, int b) {
		// TODO Auto-generated method stub
		return a-b;
	}

	@Override
	public int times(int a, int b) {
		// TODO Auto-generated method stub
		return a*b;
	}

	@Override
	public int divide(int a, int b) {
		// TODO Auto-generated method stub
		return a/b;
	}
	
}
