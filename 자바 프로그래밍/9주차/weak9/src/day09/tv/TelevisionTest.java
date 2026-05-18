package day09.tv;

public class TelevisionTest {
	static int num = 100;
	public static void main(String[] args) {
		Television t = new Television(3,8, true);
		Television t2 = new Television(6,10,false);
		Television t3 = new Television();
		t3.setTurnOff(true);
		
		Television[] ta = {t,t2,t3};
		for(Television list:ta) {
			System.out.println(list.toString());
		}
		System.out.println(t3.getChannel());
	}

}
