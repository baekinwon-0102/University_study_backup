package weak10.exam01;

import javax.swing.JOptionPane;

public class NumberException {

	public static void main(String[] args) {
		String answer = JOptionPane.showInputDialog("1부터 10까지의 정수만 입력하세요"); // 입력창 띄움
		int num = Integer.parseInt(answer); // 정수로 변환 과정 필수
		try {
			if(num < 1 || num > 10)
				throw new MyException("1~10까지의 정수값만 입력할 수 있습니다.");
		} catch (MyException e) {
			System.out.println(e.getMessage());
		}
		
	}

}
