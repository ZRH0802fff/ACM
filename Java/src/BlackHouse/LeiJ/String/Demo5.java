package BlackHouse.LeiJ.String;

public class Demo5 {
    public static void main(String[] args) {
        String s = "371522200708020039";
        String s1 = s.substring(6, 10);
        String s2 = s.substring(10, 12);
        String s3 = s.substring(12, 14);
        char s4 = s.charAt(16);
        String f1 = s1 + "年" + s2 + "月" + s3 + "日";
        String f2 = "";
        int num=s4-48;
        if (num%2==1) {
            f2 = f2 + "男";
        } else f2 = f2 + "女";
        System.out.println(f1);
        System.out.println(f2);
    }
}
