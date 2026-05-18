package day09.exam;

public class Pizza {
	private String topping;
	private static int count = 0;
	
	public Pizza() {
		this("불고기");
	}
	public Pizza(String t) {
		this.topping = t;
		count++;
	}
	@Override
	public String toString() {
		return "토핑:" + topping+" 팔린 피자 개수"+count;
	}
	public String getTopping() {
		return topping;
	}
	public void setTopping(String topping) {
		this.topping = topping;
	}
	public static int getCount() { // static 붙이는거 기말나옴
		return count;
	}
	public static void setCount(int count) {
		Pizza.count = count; // static 쓰면 this 사용 안하고 클래스.멤버변수임
	}
	
	
	
	
}
