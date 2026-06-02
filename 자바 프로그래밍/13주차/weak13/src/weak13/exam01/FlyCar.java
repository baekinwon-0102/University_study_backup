package weak13.exam01;

public class FlyCar extends Car implements Flying,Drive{

	@Override
	public void drive() {
		// TODO Auto-generated method stub
		System.out.println("자동차가 달리고 있습니다.");
	}

	@Override
	public void fly() {
		// TODO Auto-generated method stub
		System.out.println("자동차가 날고 있습니다.");
	}

	@Override
	public void speed() {
		// TODO Auto-generated method stub
		Drive.super.speed();
	}
	
}
