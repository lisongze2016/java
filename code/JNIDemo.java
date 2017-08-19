/*
编译:		javac JNIDemo.java
		export LD_LIBRARY_PATH=.
		java JNIDemo

自动生成字段描述符：
		javac JNIDemo.java
		javah -jni JNIDemo
*/

public class JNIDemo {

	/* 静态代码块，加载库只执行一次 */
		static {
			/* 1. load 加载libnative.so */
			System.loadLibrary("native");/* libnative.so */
		}

	//public native static void hello();//声明
	public native void hello();//声明
	public native int myprintf(int m);
	public native String display_string(String str);
	public native int display_data(int a[]);
	public native int[] display_array(int a[]);

	public static void main(String args[]){

		JNIDemo d = new JNIDemo();
		int a[] = {1, 2, 3, 4, 5};
		int b[] = null;
		int i;
		/* 2. java <--> c 建立映射关系 */

		/* 3.调用 */
		d.hello();
		System.out.println(d.myprintf(123));
		System.out.println(d.display_string("this is java jni demo"));
		System.out.println(d.display_data(a));
		b = d.display_array(a);

		for(i = 0; i < b.length; i++)
			System.out.println(b[i]);
	}

	public void myCallBack(byte[] jbuf){
		int i = 0;
		System.out.println("call -------->myCallBack in java");
		for(i = 0; i < jbuf.length; i++)
			System.out.println(jbuf[i]);
		System.out.println(new String(jbuf));

	}
}
