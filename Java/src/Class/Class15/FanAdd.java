package Class.Class15;

public class FanAdd {
    public static void main(String[] args) {
        int sum1=(1+1);
        double sum2=(1.0+1);
        double sum3=(1.0+1.0);
        System.out.println(sum1);
        System.out.println(sum2);
        System.out.println(sum3);
    }

    public static <T extends Number> double sum(T a,T b){
        return a.doubleValue()+b.doubleValue();
    }
}
