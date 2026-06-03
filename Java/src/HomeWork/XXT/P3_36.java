package HomeWork;

import java.util.Scanner;

public class P3_36 {
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int num=sc.nextInt();
        for (int i = 2; i <= num; i++) {
            while (num % i == 0) {
                System.out.print(i + " ");
                num/= i;
            }
        }
    }
}
