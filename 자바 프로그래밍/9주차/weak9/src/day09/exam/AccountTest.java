package day09.exam;

public class AccountTest {

	public static void main(String[] args) {
		Account obj = new Account();
		obj.setNum(1111111);
		obj.setName("백인원");
		obj.setMoney(1000);
		obj.num = 333333;
		
		System.out.println(obj.getName()+"("+obj.getNum()+")의 예금액은"+obj.getMoney());
	}

}
