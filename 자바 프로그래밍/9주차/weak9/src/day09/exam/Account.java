package day09.exam;
// 이름 계좌번호 예금액 (private)
public class Account {
	int num; // 자식 클래스 접근 허용
	public String name;
	private int money;
	public int getNum() {
		return num;
	}
	public void setNum(int num) {
		this.num = num;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public int getMoney() {
		return money;
	}
	public void setMoney(int money) {
		this.money = money;
	}
	
}
