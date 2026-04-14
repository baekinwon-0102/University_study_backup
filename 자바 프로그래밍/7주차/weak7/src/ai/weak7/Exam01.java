package ai.weak7;

public class Exam01 {

	public static void main(String[] args) {
		Box b1 = new Box(10,10,5);
		Box b2 = new Box(10,10);
		Box b3 = new Box();
		Box[] bo = {b1,b2,b3};
		for(Box b: bo) {
			System.out.println(b.extend());
		}
	}

}
