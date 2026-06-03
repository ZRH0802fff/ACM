package BlackHouse.LeiJ.String;

import java.util.Scanner;

public class Demo2 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String s=sc.next();
        int sumb=0;
        int sums=0;
        int sumn=0;
        for(int i=0;i<s.length();i++){
            char c=s.charAt(i);
            if(c>='a'&&c<='z')  sums++;
            else if (c>='A'&&c<='Z') sumb++;
            else sumn++;
        }
        System.out.println(sumb+" "+sumn+" "+sums);
    }
}
