package HomeWork.PTA.P7;

import java.util.Scanner;

public class P7_2 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int []arr=new int[10];
        for(int i=0;i<10;i++)
            arr[i]=sc.nextInt();
        int n=sc.nextInt();
        for(int i=0;i<n;i++){
            int temp=sc.nextInt();
            arr[temp-1]+=10;
        }
        for(int i=0;i<10;i++) {
            if (i < 9)
                System.out.print(arr[i] + " ");
            else
                System.out.println(arr[i]);
        }
    }
}
