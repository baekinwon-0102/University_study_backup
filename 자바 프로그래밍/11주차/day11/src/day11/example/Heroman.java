package day11.example;

public class Heroman extends Hero1{
	private String level;
	public Heroman(String name,String level) {
		super(name);
		this.level = level;
	}
	@Override
	public String toString() {
		return super.toString()+"이 "+level+"로 이동";
	}
	
}
