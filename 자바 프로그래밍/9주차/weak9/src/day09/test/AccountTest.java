package day09.test;

import day09.exam.Account;

public class AccountTest {

	public static void main(String[] args) {
		Account obj = new Account();
		obj.setNum(33333);
		obj.setName("백인투");
		System.out.println(obj.getName()+"("+obj.getNum()+")");
	}

}
