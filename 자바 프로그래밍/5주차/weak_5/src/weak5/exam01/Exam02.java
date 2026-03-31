package weak5.exam01;

public class Exam02 {

	public static void main(String[] args) {
		// works 배열에 아르바이트 한 주당 시간을 저장(월요일 부터 일요일까지 몇시간 씩 일했는지)
		// 평일 시급: 만원
		// 주말 시급: 만삼천원
		int works[] = {3,5,0,3,5,5,5}; // 순서대로 월화수목금토일
		int money=0;
		for(int i = 0;i<works.length;i++) {
			if(i<5) {
				money+=works[i]*10000;
			}
			else {
				money+=works[i]*13000;
			}
		}
		System.out.println("총 시급은 "+money+"원 입니다.");
	}

}
