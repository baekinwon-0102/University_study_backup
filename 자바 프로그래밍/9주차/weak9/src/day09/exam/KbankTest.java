package day09.exam;

public class KbankTest {

	public static void main(String[] args) {
		Kbank k1 = new Kbank("백인원",1000,0.3);
		System.out.println(k1);
		
		Kbank k2 = new Kbank("백인투",2000,0.5);
		
		System.out.println("=====0.5로 이율 변동=====");
		System.out.println(k1);
		System.out.println(k2);
		
		Kbank k3 = new Kbank("백인쓰리",1000,0.7);
		
		System.out.println("=====0.7로 이율 변동=====");
		System.out.println(k1);
		System.out.println(k2);
		System.out.println(k3);
	}

}
