package HomeWork.PTA.P7;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class P7_3 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            list.add(sc.nextInt());
        }
        int k = sc.nextInt();
        for (int i = 0; i < k; i++) {
            int x = sc.nextInt();
            list.remove(x - 1);
        }
        for (int i = 0; i < list.size(); i++) {
            if (i > 0) System.out.print(" ");
            System.out.print(list.get(i));
        }
    }
}
