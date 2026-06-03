package HomeWork.PTA.P7P9;

import java.util.Random;
import java.util.Scanner;

public class Test2 {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long seed = scanner.nextLong();
        int n = scanner.nextInt();
        Random r = new Random(seed);
        int count = 0;
        for (int i = 0; i < n; i++) {
            double x = r.nextDouble() * 2 - 1;
            double y = r.nextDouble() * 2 - 1;
            double d = Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2));
            if (d < 1)  count++;
        }
        double pi = 4.0 * count/ n;
        System.out.println(pi);
    }
}