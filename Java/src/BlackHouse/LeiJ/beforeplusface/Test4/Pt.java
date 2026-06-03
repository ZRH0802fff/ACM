package BlackHouse.LeiJ.beforeplusface.Test4;

public class Pt extends Teacher implements Learn{
    public Pt(String name, int age) {
        super(name, age);
    }

    public Pt() {
    }

    @Override
    public void work() {
        System.out.println("教乒乓球");
    }

    @Override
    public void speak() {
        System.out.println("乒乓球老师学英语");
    }
}
