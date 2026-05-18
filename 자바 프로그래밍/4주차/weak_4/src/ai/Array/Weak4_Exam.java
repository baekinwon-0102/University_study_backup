package ai.Array;

import java.util.Scanner;

public class Weak4_Exam {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		// 1 2 3 4 5 6 7 8 9
		// 0 0 0 0 0 0 0 0 0
		// 원하는 좌석번호를 입력하세요 (종료는 -1입니다)
		// 1인 곳은 이미 예약된 자리입니다 뜨게 하기
		int i =0;
		int snum[] = {0,0,0,0,0,0,0,0,0};
		while(i!=-1) {
			for(int j =0;j<9;j++) {
				System.out.print((j+1)+" ");
			}
			System.out.println();
			for(int sn:snum) {
				System.out.print(sn+" ");
			}
			System.out.println();
			System.out.print("원하는 좌석번호 입력(종료는 -1): ");
			i = scan.nextInt();
			if(i==-1) {
				break;
			}
			else if(snum[i-1]==0) {
				System.out.println("예약되었습니다.");
				snum[i-1]=1;
			}
			else if(snum[i-1]==1) {
				System.out.println("이미 예약된 좌석입니다.");
			}
		}
	}

}
