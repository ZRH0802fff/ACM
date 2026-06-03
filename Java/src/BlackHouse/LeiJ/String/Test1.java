package BlackHouse.LeiJ.String;

import java.util.Scanner;

public class Test1 {
    public static void main(String[] args) {
        Scanner sc =new Scanner(System.in);
        String s =sc.next();
        if(!check(s)) {
            System.out.println("输入错误");
            return;
        }
        StringBuilder sb=new StringBuilder();
        for(int i=0;i<s.length();i++){
            char c= s.charAt(i);
            int num=c-48;
            sb.append(change(num));
        }
        String f=sb.toString();
        System.out.println(f);
    }

    public static String change(int num){
        String arr[]={""," I "," II "," III "," IV "," V "," VI "," VII "," VIII "," IX "};
        return arr[num];
    }

    public static boolean check(String s){
        if(s.length()>9) return false;
        for(int i=0;i<s.length();i++){
            char c =s.charAt(i);
            if(c<'0'||c>'9')  return false;
        }
        return true;
    }
}
