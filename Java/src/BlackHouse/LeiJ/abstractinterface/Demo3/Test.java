package BlackHouse.LeiJ.abstractinterface.Demo3;

public class Test {
    public static void main(String[] args) {
        //1.1子类实现接口
        System.out.println("=== 子类实现接口 IPlay 调用方式 ===");
        class iii implements IPlay{
            @Override
            public void playGame() {
                System.out.println("子类实现接口：正在玩游戏");
            }
        }
        //创建对象开始实现
        iii i=new iii();
        i.playGame();

        //1.2匿名内部类实现接口
        System.out.println("=== 匿名内部类实现接口 IPlay 调用方式 ===");
        //
        new IPlay() {
            @Override
            public void playGame() {
                System.out.println("匿名内部类实现接口：正在玩游戏");
            }
        }.playGame();

        System.out.println("\n=== 子类实现抽象类 Fun 调用方式 ===");
        class ooo extends Fun{
            @Override
            void fun() {
                System.out.println("子类继承抽象类：正在fun");
            }
        }
        ooo o=new ooo();
        o.fun();
        System.out.println("=== 匿名内部类实现抽象类 Fun 调用方式 ===");
        new Fun(){
            @Override
            void fun() {
                System.out.println("匿名内部类继承抽象类：正在fun");
            }
        }.fun();
    }
}
