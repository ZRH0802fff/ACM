package HomeWork.PTA.P7;

import java.util.Scanner;

public class P7_1 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int []arr=new int [10];
        int sum=0;
        for(int i=0;i<10;i++){
            arr[i]=sc.nextInt();
            sum+=arr[i];
        }
        double avg=sum/10.0;
        System.out.printf("%.2f",avg);
    }
}
