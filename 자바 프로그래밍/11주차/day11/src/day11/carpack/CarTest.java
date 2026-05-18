package day11.carpack;
class Car{
	private int oil;
	public Car(int oil) {
		this.oil = oil;
	}
	public void disp() {
		System.out.print("잔여기름량은 = "+oil);
	}
	
}

class Hibrid extends Car{
	private int elec;
	public Hibrid(int oil, int elec) {
		super(oil);
		this.elec = elec;
	}
	@Override
	public void disp() {
		super.disp();
		System.out.print(", 잔여전력량은 = "+elec);
	}
	
}

class Hwater extends Hibrid{
	private int water;
	public Hwater(int oil, int elec, int water) {
		super(oil,elec);
		this.water = water;
	}
	@Override
	public void disp() {
		super.disp();
		System.out.print(", 잔여수소량은 = "+water);
	}
	
	
}

public class CarTest {

	public static void main(String[] args) {
		Car c1 = new Car(100);
		Car c2 = new Hibrid(50,50);
		Car c3 = new Hwater(30,30,30);
		Car[] c = {c1,c2,c3};
		for(Car li:c) {
			li.disp();
			System.out.println();
		}
	}

}
