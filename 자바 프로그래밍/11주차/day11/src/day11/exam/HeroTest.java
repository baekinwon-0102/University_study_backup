package day11.exam;

public class HeroTest {

	public static void main(String[] args) {
		Hero h1 = new Superman("슈퍼맨","망토");
		Hero h2 = new Batman("배트맨","오토바이");
		Hero h3 = new SpiderMan("스파이더맨","거미줄");
		Hero[] h = {h1,h2,h3};
		for(Hero li:h)
			li.Move();
	}

}
