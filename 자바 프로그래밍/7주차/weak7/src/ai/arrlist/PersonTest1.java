package ai.arrlist;

import java.util.ArrayList;

public class PersonTest1 {

	public static void main(String[] args) {
		// ArrayList 클래스를 사용해 3명 친구의 이름과 전화번호를 추가하고 출력하기
		
		ArrayList<Person> p = new ArrayList<Person>();
		p.add(new Person("백인원","010-6792-5119"));
		p.add(new Person("김건우","010-1234-5312"));
		p.add(new Person("노태권","010-3863-5793"));
		for(Person li:p) {
			System.out.println(li.toString());
		}
		
	}

}
