package day11.study;
// 슈퍼클래스 x, y 좌표: protected
// 메서드: 출력(10,10)
public class Point {
	private int x,y;
	public Point(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public void showPoint() {
		System.out.println("("+x+","+y+")");
	}
}
