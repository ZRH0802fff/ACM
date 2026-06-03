package Class.Before11.Test1;

import java.util.Scanner;

public class P1Test {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String page = sc.next();
        String name = sc.next();
        double value = sc.nextDouble();

        P1 p1 = new P1(page, name, value);

        String output = p1.toString();
        output = output.replace("P1{page = ", "")
                .replace(", name = ", ",")
                .replace(", value = ", ",")
                .replace("}", "");
        System.out.println(output);

        sc.close();
    }
}
