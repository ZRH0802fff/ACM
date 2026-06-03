package BlackHouse.LeiJ.DuoTai.Test1;

public class Dog extends Animal {

    public Dog() {
    }

    public Dog(String name, String coloar) {
        super(name, coloar);
    }

    public void lookhome(){
        System.out.println("狗在看家");
    }

    @Override
    public void eat( String food) {
        System.out.println(getName()+ "岁的" + getColoar() + "颜色的狗两只前腿死死的抱住" + food + "猛吃");
    }
}
