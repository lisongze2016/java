/* 有中文注释编译用 javac -encoding UTF-8 */
/* Object Oriented Programming */
class Person{

	/* 类属型 */
	static int count;
	static int cnt;
	String name;
	int age;
	String getName(){
		return "guangdong "+name;
	}
	/* 静态代码块 实例化第一个对象前执行，并且执行一次*/
	static {
		System.out.println("static block");	
	}
	/* 构造块 每实例化一个对象前都执行，先于构造方法执行*/
	{
		System.out.println("construct block");
		count ++;
	}
	/* 构造方法 不能有返回值 */
	public Person (){
		System.out.println("construct method: Person 1");
		cnt++;
		name = "null";
		age  = 0;
	}
	/* 普通代码块 */
	public Person (String name){
		System.out.println("construct method: Person 2");
		cnt++;
		/* this关键字，表示当前对象或当前类 */
		this.name = name;
	}
	/* 普通代码块 */
	public Person (String name, int age){
		System.out.println("construct method: Person 3");
		cnt++;
		this.name = name;
		this.age  = age; 
	}
	/* static  类方法 */
	static void printPerson (){
		System.out.println("This is a class of Person");
	}
};

public class Oop {
	public static void main(String args[]){
		/* 通过类来定义变量，即创建对象 */
		Person p1 = new Person("zhangsan");
		Person p2 = new Person("lisi");
		Person p3 = new Person();
		Person p4 = new Person("wangwu", 6);

		System.out.println(p1.getName());
		System.out.println(p2.getName());
		System.out.println(p3.getName());
		System.out.println(p4.getName());

		Person.printPerson();
		System.out.println(Person.cnt);
		System.out.println(Person.count);
	}
}

