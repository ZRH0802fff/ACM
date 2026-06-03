package BlackHouse.LeiJ.String;

import java.util.Scanner;

public class Demo6 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String s=sc.next();
        String f=new StringBuilder().append(s).reverse().toString();
        if(s.equals(f))  System.out.println("Yes");
        else System.out.println("No");
    }
}
