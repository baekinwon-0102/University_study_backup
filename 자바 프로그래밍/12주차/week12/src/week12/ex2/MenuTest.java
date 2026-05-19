package week12.ex2;

public class MenuTest {

	public static void main(String[] args) {
		Buyer b1 = new Buyer(20000);
		b1.buy(new Noodle(), 2);
		b1.buy(new Woodong(), 1);
	}

}
