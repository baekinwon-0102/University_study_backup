package day11.exam;

public abstract class Hero {
	protected String name;
	public Hero(String name) {
		this.name = name;
	}
	public abstract void Move();
}
