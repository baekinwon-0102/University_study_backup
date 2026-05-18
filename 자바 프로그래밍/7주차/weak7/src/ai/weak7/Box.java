package ai.weak7;

public class Box {
	int width, height, depth;
	public Box() {
		this(1, 1, 1);
	}
	public Box(int width,int height,int depth){
		this.width=width;
		this.height=height;
		this.depth=depth;
	}
	public Box(int width, int height) {
		this();
		this.width = width;
		this.height = height;
	}
	public int extend() {
		return width*height*depth;
	}
}
