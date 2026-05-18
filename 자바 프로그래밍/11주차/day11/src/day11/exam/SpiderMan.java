package day11.exam;

public class SpiderMan extends Hero{
	private String level;
	public SpiderMan(String name, String level) {
		super(name);
		this.level = level;
	}
	@Override
	public void Move() {
		System.out.println(name+"이 "+level+"로 이동");
	}
	
}
