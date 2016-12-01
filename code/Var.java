
public class Var {
	public static void main(String args[]){
		/* c 语言定义变量如下
		int a = 3;
		float f = 3.14;
		int *p = malloc(10*sizeof(int));
		int p2[] = {1,2,3};
		char str[100];
		char str2[] = "abc";
		*/

		/* 对应java定义变量如下 */

		int a = 3;
		float f = 3.14f;	//float f = 3.14;//不兼容的类型: 从double转换到float可能会有损失
		int p[] = new int[10];
		int p2[] = {1,2,3};
		char str[] = new char[100];
		String str2 = "abc";

		/* 强制类型转换 */
		short s = 1;
		s = (short)(s + 1);//s = s + 1;//出错 对于byte short的运算，为了保证精度，会自动转换为int

		/* free */
		p = null;
		p2 = null;
		str = null;
		str2 = null;
	}
}