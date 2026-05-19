package week12.ex2;

public abstract class Item { // 반드시 추상메서드가 있어야 하는건 아님
	protected int price;
}

class Noodle extends Item{
	public Noodle() {
		super.price = 5000;
	}

	@Override
	public String toString() {
		return "국수";
	}
	
}

class Woodong extends Item{
	public Woodong() {
		super.price = 6000;
	}

	@Override
	public String toString() {
		return "우동";
	}
	
}

class Mixnoodle extends Item{
	public Mixnoodle() {
		super.price = 7000;
	}

	@Override
	public String toString() {
		return "비빔국수";
	}
	
}