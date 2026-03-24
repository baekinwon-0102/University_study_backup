package ai.weak_4;

public class ContinueWhile {

	public static void main(String[] args) {
		int i = 0;
		while(i<10) {
			i++;
			if(i==5) continue;
			System.out.print(i+" ");
		}
	}

}
