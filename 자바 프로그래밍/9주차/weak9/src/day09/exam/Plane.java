package day09.exam;

public class Plane {
	// Plane 클래스의 객체를 만드는 PlanTest를 만들어 다음 과같이 출력
	// Plane 클래스 멤버 필드 : 제작사, 모델, 최대 승객수
	private String make;
	private String model;
	private int maxpass;
	private static int count=0;
	public Plane() {
		this("airbus","A380",500);
	}
	public Plane(String make, String model, int maxpass) {
		this.make = make;
		this.model = model;
		this.maxpass = maxpass;
		count++;
	}
	@Override
	public String toString() {
		return "비행기 모델: " + model + ", 승객수: " + maxpass + ", 제조사: " + make;
	}
	public String getMake() {
		return make;
	}
	public void setMake(String make) {
		this.make = make;
	}
	public String getModel() {
		return model;
	}
	public void setModel(String model) {
		this.model = model;
	}
	public int getMaxpass() {
		return maxpass;
	}
	public void setMaxpass(int maxpass) {
		this.maxpass = maxpass;
	}
	public static int getCount() {
		return count;
	}
	public static void setCount(int count) {
		Plane.count = count;
	}
	
	
}
