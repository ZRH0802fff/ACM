package HomeWork.PTA.P7;

import java.util.Scanner;

public class P7_5 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        boolean[] seen = new boolean[100001];

        for (int i = 0; i < n; i++) {
            int num = sc.nextInt();
            if (seen[num]) {
                System.out.println("YES");
                return;
            }
            seen[num] = true;
        }
        System.out.println("NO");
        sc.close();
    }
}
