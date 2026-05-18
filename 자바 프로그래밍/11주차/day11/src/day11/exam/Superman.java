package day11.exam;

public class Superman extends Hero{
	private String level;
	public Superman(String name, String level) {
		super(name);
		this.level = level;
	}
	@Override
	public void Move() {
		System.out.println(name+"이 "+level+"로 이동");
	}
	
}
