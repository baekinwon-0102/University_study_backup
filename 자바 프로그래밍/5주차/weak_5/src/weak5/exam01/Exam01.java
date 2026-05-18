package weak5.exam01;

import java.util.Scanner;

public class Exam01 {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int[] num_list = new int[5];
		int max,min;
		num_list[0] = scan.nextInt();
		max = num_list[0];
		min = num_list[0];
		for(int i = 1;i<num_list.length;i++) {
			num_list[i] = scan.nextInt();
			if(max < num_list[i]) {
				max = num_list[i];
			}
			
			if(min > num_list[i]) {
				min = num_list[i];
			}
		}
		System.out.println("최댓값: "+max+" 최솟값: "+min);
	}

}
