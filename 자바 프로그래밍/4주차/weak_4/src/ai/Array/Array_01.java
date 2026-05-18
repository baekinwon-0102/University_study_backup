package ai.Array;

public class Array_01 {

	public static void main(String[] args) {
		// 정수형 배열 선언하고 1부터 10까지 저장
		int a[] = new int[10];
		int sum=0;
		for(int i=0;i<a.length;i++) {
			a[i] = i+1;
			//System.out.println("a["+i+"] = "+a[i]);
		}
		//for~each문
		// for(자료형(클래스이름) 받아올정의할이름: 배열의이름)
		for(int alist: a) {
			sum+=alist;
		}
		System.out.print("배열 요소의 합은: "+sum);
	}

}
