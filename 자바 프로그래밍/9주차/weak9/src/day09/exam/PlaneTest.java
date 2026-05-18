package day09.exam;

public class PlaneTest {

	public static void main(String[] args) {
		Plane p1 = new Plane("Asiana","Boeing 737",800);
		Plane p2 = new Plane("Korea","Boeing 800",900);
		Plane p3 = new Plane();
		
		Plane[] p = {p1,p2,p3};
		
		System.out.println("비행기 개수:"+Plane.getCount());
		for(Plane li:p) {
			System.out.println(li);
		}
	}

}
