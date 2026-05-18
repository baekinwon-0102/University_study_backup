package weak10.exam01;

public class Ex02 {

	public static void main(String[] args) {
		int[] num = {10,20,30,40,50};
		try {
			for(int i = 0;i<=num.length;i++) {
				System.out.print(num[i]+" ");
			}
		} catch (ArrayIndexOutOfBoundsException e) {
			System.out.println("배열의 크기가 벗어났습니다.");
		}finally {
			System.out.println("크기를 확인하세요");
		}
	}

}
