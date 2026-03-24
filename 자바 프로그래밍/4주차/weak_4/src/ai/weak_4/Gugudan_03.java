package ai.weak_4;

public class Gugudan_03 {

	public static void main(String[] args) {
		// 3단과 8단을 제외하고 출력하고 단보다 곱해지는 값이 커지면 종료
		for(int i =2;i<=9;i++) {
			if(i ==3 || i==8) continue;
			
			for(int j = 1;j<=9;j++) {
				if (i<j) break;
				System.out.println(i+" X "+j+" = "+(i*j));
			}
			System.out.println();
		}
	}

}
