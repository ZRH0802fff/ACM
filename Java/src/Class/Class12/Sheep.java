package Class.Class12;

public class Sheep extends anm{
    public Sheep() {
    }

    public Sheep(String name, int age) {
        super(name, age);
    }

    @Override
    public void eat() {
        System.out.println("吃草");
    }
}
