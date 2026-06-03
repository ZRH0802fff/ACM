package BlackHouse.LeiJ.String;

import java.util.Random;
import java.util.Scanner;

public class Test3 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String s=sc.next();
        char arr[]=s.toCharArray();
        Random r=new Random();
        for(int i=0;i<arr.length;i++){
            int index=r.nextInt(arr.length);
            char t=arr[i];
            arr[i]=arr[index];
            arr[index]=t;
        }
        String f=new String(arr);
        System.out.println(f);
    }
}
