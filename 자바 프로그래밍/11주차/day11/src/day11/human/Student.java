package day11.human;

public class Student extends Man{
	private int grade;
	public Student(String name, String dept,int g) {
		super.name = name;
		super.dept = dept;
		this.grade = g;
	}
	@Override
	public void Print() {
		super.Print();
		System.out.println(" "+grade+"학년");
	}
	
	
}
