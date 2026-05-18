package ai.arrlist;

// 이름 전화번호 출력 메서드 모든 값 초기화

public class Person {
	String name, tel;
	public Person() {
		this(" "," ");
	}
	public Person(String name, String tel) {
		this.name = name;
		this.tel = tel;
	}
	@Override
	public String toString() {
		return name + ":"+ tel;
	}
	
}
