package day11.study;

public class PointTest {

	public static void main(String[] args) {
		Point p = new Point(10,10);
		ColorPoint cp = new ColorPoint(100,100,"red");
		p.showPoint();
		cp.showPoint();
		cp.colorPoint();
	}

}
