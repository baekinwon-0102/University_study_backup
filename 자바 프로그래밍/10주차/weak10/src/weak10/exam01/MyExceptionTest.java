package weak10.exam01;

public class MyExceptionTest {

	public static void main(String[] args) {
		try {
			throw new MyException("내가 만든 예외클래스");
		} catch(MyException e) {
			System.out.println(e.getMessage());
		}
	}

}
