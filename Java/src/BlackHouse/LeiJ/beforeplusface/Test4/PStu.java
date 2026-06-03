package BlackHouse.LeiJ.beforeplusface.Test4;

public class PStu extends Stu implements Learn{
    public PStu() {
    }

    public PStu(String name, int age) {
        super(name, age);
    }

    @Override
    public void work() {
        System.out.println("学乒乓球");
    }

    @Override
    public void speak() {
        System.out.println("乒乓球运动员学英语");
    }
}
