/* 函数重载 */
public class Function {
	public static void main(String args[]){
		System.out.println("1+2 = "+add(1,2));
		System.out.println("1+2+3 = "+add(1,2,3));
		System.out.println("1.0f+2.0f = "+add(1.0f,2.0f));
	}
	
	public static int add(int x, int y){
		return x + y;
	}
	public static int add(int x, int y, int z){
		return x + y + z;
	}
	public static float add(float x, float y){
		return x + y;
	}
}