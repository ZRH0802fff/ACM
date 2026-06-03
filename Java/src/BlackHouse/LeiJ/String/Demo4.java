package BlackHouse.LeiJ.String;

public class Demo4 {
    public static void main(String[] args) {
        String s="12345678901";
        String s1=s.substring(0,3);
        String s2=s.substring(7,11);
        String f=s1+"****"+s2;
        System.out.println(f);
    }
}
