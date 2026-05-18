package weak6.cla;

// Pizza 클래스 정의: 크기 종류 사이드메뉴
// 불고기 16인치 사이드: 스파게티 주문 처럼 출력
// 모든 값을 초기화하는 생성자정의
// 종류와 크기를 초기화하는 생성자정의
// 객체 생성해 출력

class Pizza{
	double size;
	String type;
	String side;
	
	public Pizza() { // default 생성자 생성
		this(12,"콤비네이션 피자","사이드 없음");
	}
	
	public Pizza(double size, String type, String side) {
		this.size = size;
		this.type = type;
		this.side = side;
	}
	
	public Pizza(String type, String side) {
		this();
		this.type = type;
		this.side = side;
	}
	
	public Pizza(double size, String type) {
		this(); // 생성자에서 또다른 생성자 호출 (반드시 맨 위에 호출 밑에서 호출 시 에러남) 
		this.size = size;
		this.type = type;
		// default 생성자를 호출했으니 this.side는 "사이드 없음"이 됨
	}

	@Override
	public String toString() {
		return type+", size=" + size + ", side=" + side;
	}

	// toString() 메서드 오버라이딩(재정의) -> 이클립스 Source메뉴 -> Generate toString 클릭 -> 사용할 변수들 클릭 후 Generate
	
}

public class Test02 {

	public static void main(String[] args) {
		Pizza p1 = new Pizza(16,"불고기 피자","스파게티");
		Pizza p2 = new Pizza(14,"고르곤졸라 피자");
		Pizza p3 = new Pizza();
		Pizza p4 = new Pizza("슈프림 피자","떡볶이");
		// toString() : java.lang.Object 클래스에 정의(문자열 반환함)
		// 지금있는 패키지 주소와 클래스명을 출력함
		// 인스턴스만 출력해도 toString 내용일 출력됨
		
		Pizza[] p ={p1,p2,p3,p4};
		for(Pizza pq:p) {
			System.out.println(pq);
		}
	}

}
