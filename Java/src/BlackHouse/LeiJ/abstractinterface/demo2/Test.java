package BlackHouse.LeiJ.abstractinterface.demo2;

public class Test {
    public static void main(String[] args) {
        Phone p=new NewPhone();

        f (p);

    }
    public static void f(Phone p){
        p.Talk();
        p.Message();
        if(p instanceof NewPhone np ){
            np.playgame();
        }
    }
}
