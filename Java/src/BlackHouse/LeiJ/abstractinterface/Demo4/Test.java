package BlackHouse.LeiJ.abstractinterface.Demo4;

interface Inter {
    void show();
}
class Outer {
    public static Inter method(){
        return new Inter() {
            @Override
            public void show() {
                System.out.println("HelloWorld");
            }
        };
    }
}
public class Test {
    public static void main(String[] args) {
        Outer.method().show();
    }
}
