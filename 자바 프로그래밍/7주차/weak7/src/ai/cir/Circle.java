package ai.cir;

public class Circle {
	int r;
	public Circle(){
		this(1);
	}
	public Circle(int radius){
		this.r = radius;
	}
	public double getRe() {
		return 3.14 * r * r;
	}
}
