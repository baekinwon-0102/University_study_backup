package ai.Array;

public class Array_03 {

	public static void main(String[] args) {
		char scores[] = {'X','O','O','X','O','O','X','O','O','X'};
		// 1문제당 10점씩입니다 맞은 개수의 점수를 출력
		int sum=0;
		for(char sc:scores) {
			if(sc == 'O') sum++;
		}
		System.out.println("정답 개수: "+sum);
		System.out.println("점수: "+sum*10);
	}

}
