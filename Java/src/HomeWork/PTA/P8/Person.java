package HomeWork.PTA.P8;

public class Person implements Biology,Animal{
    @Override
    public void eat() {
        System.out.println("我会按时吃饭");
    }

    @Override
    public void sleep() {
        System.out.println(("早睡早起身体好"));
    }

    @Override
    public void breath() {
        System.out.println("我喜欢呼吸新鲜空气");
    }
    public void think(){
        System.out.println("我喜欢思考");
    }
}
