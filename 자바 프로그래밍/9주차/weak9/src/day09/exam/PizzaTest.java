package day09.exam;

public class PizzaTest {

	public static void main(String[] args) {
		Pizza p1 = new Pizza("치즈");
		Pizza p2 = new Pizza("페퍼로니");
		Pizza p3 = new Pizza("슈프림");
		Pizza p4 = new Pizza();
		
		
		
		Pizza[] p = {p1,p2,p3,p4};
		for(Pizza li:p) {
			System.out.println(li);
		}
		System.out.println("지금까지 판매한 피자 개수:"+Pizza.getCount());
	}

}
