package weak13.exam01;

public interface Drive{
	public void drive();
	default public void speed() {
		System.out.println("규정속도 30km/h로 달리고 있습니다.");
	}
}