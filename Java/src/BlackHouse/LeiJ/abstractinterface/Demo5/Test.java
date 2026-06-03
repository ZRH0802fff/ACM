package BlackHouse.LeiJ.abstractinterface.Demo5;

public class Test {
    public static void main(String[] args) {
        //创建独立类实现
        A a1=new A();
        class subInterA implements InterA{
            @Override
            public void showA() {
                System.out.println("实现成功");
            }
        }
        subInterA s1=new subInterA();
        a1.methodA(s1);
        //匿名内部类实现
        A a2=new A();
        a2.methodA(new InterA() {
            @Override
            public void showA() {
                System.out.println("实现成功");
            }
        });
    }
}
interface InterA {
    void showA();
}

class A {
    public void methodA(InterA a) {
        a.showA();
    }
}