package week12.day19;

public class AnimalTest {

	public static void main(String[] args) {
		// 부모클래스로 업캐스팅 객체형변환을 하면 자신만의 메서드 호출 불가
		Animal c = new Cat();
		Dog d = new Dog();
		c.cry();
		c.eat();
		// c.grooming();
		d.cry();
		d.eat();
		d.lash();
		
		System.out.println(c instanceof Animal); // 객체가 Cat 클래스로 다운캐스팅 되었는지 확인 
		System.out.println(d instanceof Animal); 
	}

}
