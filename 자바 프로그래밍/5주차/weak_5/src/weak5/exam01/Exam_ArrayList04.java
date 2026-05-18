package weak5.exam01;

import java.util.ArrayList;
import java.util.Collections;

public class Exam_ArrayList04 {

	public static void main(String[] args) {
		// 1부터 45번까지 추가 출력
		ArrayList<Integer> num = new ArrayList<Integer>();
		
		for(int i = 1;i<=45;i++)
			num.add(i);
		for(int n:num)
			System.out.print(n+" ");
		Collections.shuffle(num);
		System.out.println("\n==============랜덤하게 섞고 출력=============");
		for(int n:num)
			System.out.print(n+" ");
		System.out.println("\n==============값 6개만 출력=============");
		for(int i=0;i<6;i++)
			System.out.print(num.get(i)+" ");
	}

}
