package week12.day19;

public class AnimalTest {

	public static void main(String[] args) {
		// 부모클래스로 업캐스팅 객체형변환을 하면 자신만의 메서드 호출 불가
//		Animal c = new Cat();
//		Dog d = new Dog();
//		c.cry();
//		c.eat();
//		// c.grooming();
//		d.cry();
//		d.eat();
//		d.lash();
//		
//		System.out.println(c instanceof Cat); // 객체가 업캐스팅한 객체이면 Cat 클래스인지 Dog 클래스인지 확인
//		Cat cat = (Cat)c; // 객체형변환 (다운캐스팅)
//		cat.grooming();
//		System.out.println(c instanceof Dog); 
		
		Animal a1 = new Cat();
		Animal a2 = new Dog();
		// 세번울면 냠냠 고양이: 그루밍, 개: 살랑살랑
		Animal[] animal = {a1,a2};
		for(int i = 0;i<animal.length;i++) {
			for(int j = 0;j<3;j++) {
				animal[i].cry();
			}
			animal[i].eat();
			if(animal[i] instanceof Cat) {
				Cat cat = (Cat)animal[i];
				cat.grooming();
			}else if(animal[i] instanceof Dog) {
				Dog dog = (Dog)animal[i];
				dog.lash();
			}
		}
	}

}
