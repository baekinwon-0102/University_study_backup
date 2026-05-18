package day11.exam;

public class Batman extends Hero{
	private String level;
	public Batman(String name, String level) {
		super(name);
		this.level = level;
	}
	@Override
	public void Move() {
		System.out.println(name+"이 "+level+"로 이동");
	}
}
