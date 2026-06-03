package HomeWork;

import java.util.Scanner;

public class P3_31 {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("请输入a, b, c的值: ");
        double a = input.nextDouble();
        double b = input.nextDouble();
        double c = input.nextDouble();
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            double root1 = (-b + Math.sqrt(discriminant)) / (2 * a);
            double root2 = (-b - Math.sqrt(discriminant)) / (2 * a);
            System.out.printf("方程有两个实数根：%.1f和%.1f%n", root1,"和",root2);
        } else if (discriminant == 0) {
            double root = -b / (2 * a);
            System.out.printf("方程只有一个根：%.1f%n", root);
        } else {
            System.out.println("方程无实根");
        }
    }
}
