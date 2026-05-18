package weak5.exam01;

import java.util.ArrayList;

public class Exam_ArrayList03 {

	public static void main(String[] args) {
		// 친구네명을 배열에 저장
		ArrayList<String> name = new ArrayList<String>();
		name.add("박세준");
		name.add("김건우");
		name.add("김정우");
		name.add("노태권");
		
		// 한꺼번에 친구이름 출력
		for(String n:name)
			System.out.print(n+" ");
		System.out.println("\n====1번째 요소에 친구이름 추가====");
		name.add(1,"홍석훈");
		for(String n:name)
			System.out.print(n+" ");
		System.out.println("\n====2번째 요소에 친구이름 변경====");
		name.set(2, "안찬익");
		for(String n:name)
			System.out.print(n+" ");
		System.out.println("\n====노태권 삭제====");
		name.remove("노태권");
		for(String n:name)
			System.out.print(n+" ");
		System.out.println("\n====2번째 요소에 친구이름 삭제====");
		name.remove(2);
		for(String n:name)
			System.out.print(n+" ");
		System.out.println("\n====1번째 요소에 친구이름 검색====");
		String fr = name.get(1);
		System.out.println("검색한 친구의 이름: "+fr);
		System.out.println("\n====홍석훈이 몇번째 있는지 검색====");
		int num = name.indexOf("홍석훈");
		System.out.println("홍석훈의 위치: "+(num+1)+"번째에 있음");
	}

}
