package BlackHouse.LeiJ.String;

import java.util.Scanner;

public class Test2 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String s1=sc.next();
        String s2=sc.next();
        if(s1.length()!=s2.length()) {
            System.out.println("false");
            return;
        }else {
            char []arr=s1.toCharArray();
            for(int i=0;i<s1.length();i++){
                char t=arr[0];
                for(int j=1;j<s1.length();j++){
                    arr[j-1]=arr[j];
                }
                arr[arr.length-1]=t;
                String f=new String(arr);
                if(f.equals(s2)){
                    System.out.println("True");
                    return;
                }
            }
            System.out.println("False");
        }
    }
}
