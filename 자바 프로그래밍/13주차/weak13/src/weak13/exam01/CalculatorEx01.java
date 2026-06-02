package weak13.exam01;

public class CalculatorEx01 {

	public static void main(String[] args) {
		Calculator obj = new Calculator();
		//System.out.println(obj.print());
		System.out.println(obj.add(10, 20));
		System.out.println(obj.sub(10, 20));
		System.out.println(obj.times(10, 20));
		System.out.println(obj.divide(20, 10));
		
		int[] arr = {10,20,30,40};
		System.out.println(Calc.total(arr));
	}

}
