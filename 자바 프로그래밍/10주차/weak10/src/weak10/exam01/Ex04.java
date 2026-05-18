package weak10.exam01;

import java.io.FileReader;
import java.io.IOException;

public class Ex04 {

	public static void main(String[] args) throws IOException {
		// FileReader(문자열 파일) FileInputStream(그림, 사진, 영상):read() FileWriter(파일 쓰기) FileOutputStream(파일 쓰기): write() <- 예외처리 필수
		// try-catch가 선택이 아닌 필수
		try {
			FileReader fr = new FileReader("C:\\Java_code\\test.txt");
			char[] a = new char[100];
			fr.read(a);
			System.out.println(a);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
