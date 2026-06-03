package BlackHouse.LeiJ.DuoTai.Test1;

public class Cat extends Animal{
    public Cat() {
    }

    public Cat(String name, String coloar) {
        super(name, coloar);
    }

    @Override
    public void eat(String food) {
        System.out.println(getName() + "岁的" + getColoar() + "颜色的猫眯着眼睛侧着头吃" + food);
    }

    public void catchMouse(){
        System.out.println("猫抓老鼠");
    }
}
