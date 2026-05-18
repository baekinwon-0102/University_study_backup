package ai.mov;

// Movie 클래스 정의: 영화제목 감독 toString()오버라이딩

public class Movie {
	String title, author;
	
	public Movie() {
		this(" "," ");
	}
	public Movie(String title, String author) {
		this.title = title;
		this.author = author;
	}
	@Override
	public String toString() {
		return "영화 제목은 " + title + ", 감독은 " + author + "입니다.";
	}
	
}
