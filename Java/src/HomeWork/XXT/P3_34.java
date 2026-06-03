package HomeWork;

import java.util.Scanner;

public class P3_34 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int num=sc.nextInt();
        int sum=0;
        while(num>=10){
            sum+=num%10;
            num/=10;
        }
        sum+=num;
        System.out.println("各位数字之和为："+sum);
    }
}
