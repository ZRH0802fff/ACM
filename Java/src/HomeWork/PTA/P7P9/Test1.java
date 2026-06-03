package HomeWork.PTA.P7P9;

import java.util.Scanner;

public class Test1 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = scanner.nextLine();
        f(0,s);
    }
    public static void f(int i,String s){
        int t1=s.indexOf("/",i);
        int t2=s.indexOf("/",t1+1);
        int t3=s.indexOf(",",t2+1);
        if(t3<=0){
            String t=s.substring(t2+1,s.length());
            System.out.print(t+";");
            return;
        }
        String t=s.substring(t2+1,t3);
        System.out.print(t+";");
        f(t3+1,s);
    }
}
