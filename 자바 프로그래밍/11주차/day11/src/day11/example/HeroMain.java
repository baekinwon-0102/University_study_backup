package day11.example;

import java.util.Scanner;

public class HeroMain {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		Hero1[] h = new Heroman[3];
		System.out.println("영웅과 무기를 입력하시오");
		for(int i = 0;i<h.length;i++) {
			System.out.print("영웅입력: ");
			String he = scan.next();
			System.out.print("무기입력: ");
			String le = scan.next();
			h[i] = new Heroman(he,le);
		}
		
		for(int i = 0;i<h.length;i++) {
			System.out.println(h[i].toString());
		}
	}

}
