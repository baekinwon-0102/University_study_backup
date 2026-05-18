package day11.human;

public class ManTest {

	public static void main(String[] args) {
		// Upcasting (업캐스팅): 객체형변환
		Man st = new Student("백인원", "인공지능학과",2);
		Man st2 = new Student("김정우","인공지능학과",1);
	    Man pr = new Proffessor("이순신","메카트로닉스과","부교수");
		Man pr2 = new Proffessor("오은성","인공지능과","정교수");
		Man[] m = {st,st2,pr,pr2};
		for(Man list:m) {
			list.Print();
		}
	}

}
