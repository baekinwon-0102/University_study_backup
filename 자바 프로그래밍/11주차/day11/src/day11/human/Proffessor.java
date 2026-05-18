package day11.human;

public class Proffessor extends Man{
	private String position;
	
	public Proffessor(String name, String dept, String position) {
		super.name = name;
		super.dept = dept;
		this.position = position;
	}

	@Override
	public void Print() {
		super.Print();
		System.out.println(" "+position);
	}
	
}
