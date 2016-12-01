
public class FunctionParam{
	public static void main(String args[]){
		int x = 1;
		int p[] = new int[1];
		p[0] = 123;
		System.out.println("before fun:x="+x +" p[0]="+p[0]);
		fun(x,p);
		System.out.println("after  fun:x="+x +" p[0]="+p[0]);
		
	}
	public static void fun(int x,int[] p){
		x = 100;
		p[0] = 200;
	}
}