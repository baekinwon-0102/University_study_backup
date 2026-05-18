package day09.exam;

public class Kbank {
	private String name;
	private int money;
	private static double rate;
	public Kbank(String n, int m, double r) {
		this.name = n;
		this.money = m;
		this.rate = r;
	}
	@Override
	public String toString() {
		return "[name=" + name + ", money=" + money + ", rate=" + rate + "]";
	}
	
}
