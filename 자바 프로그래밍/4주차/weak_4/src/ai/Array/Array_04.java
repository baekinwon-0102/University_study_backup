package ai.Array;

import java.util.Scanner;

public class Array_04 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		String[] kor = {"돈","주식","금","코스피","부동산"};
		String[] eng = {"money","stock","gold","cospy","estate"};
		// 입력형태는 승리를 영어로 입력
		// 답을 입력받아 20점 부여 하여 총점을 출력
		System.out.println("다음 단어를 영어로 입력하시오");
		int sum=0;
		for(int i = 0;i<kor.length;i++) {
			System.out.print(kor[i]+": ");
			String inp = scan.next();
			if(inp.equalsIgnoreCase(eng[i])) sum+=20;
		}
		System.out.println("총점: "+sum);
	}

}
