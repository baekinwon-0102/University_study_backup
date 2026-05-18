package weak10.exam01;

import java.util.Scanner;

public class LoginException {
static String userid = "baek";
static String userpwd = "1234";
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		try {
			System.out.print("아이디입력: ");
			String id = scan.next();
			System.out.print("비밀번호입력: ");
			String pwd = scan.next();
			if(!userid.equals(id))
				throw new MyException("아이디가 일치하지 않습니다.");
			else if(!userpwd.equals(pwd))
				throw new MyException("패스워드가 일치하지 않습니다.");
			else
				System.out.println("로그인 성공");
		} catch (MyException e) {
			 System.out.println(e.getMessage());
		}
		
	}

}
