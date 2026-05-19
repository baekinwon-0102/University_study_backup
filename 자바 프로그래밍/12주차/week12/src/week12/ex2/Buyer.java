package week12.ex2;

public class Buyer {
	private int money;
	public Buyer(int m) {
		this.money = m;
	}
	public void buy(Item it, int count) {
		System.out.println(it.toString()+"을(를) "+count+"개 주문");
		money = money - (it.price*count);
		System.out.println("당신의 남은 돈은 "+money+"입니다.");
	}
}
