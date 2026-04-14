package ai.assignment;

public class Student {
	String name, grade;
	int kor,eng,math;
	double avg;
	
	public Student() {
		this("",1,1,1);
	}
	public Student(String n, int k, int e, int m) {
		this.name = n;
		this.kor = k;
		this.eng = e;
		this.math = m;
	}
	
	@Override
	public String toString() {
		return name+"/"+avg+"/"+grade+"학점";
	}
	
}
