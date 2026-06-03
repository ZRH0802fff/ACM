package HomeWork.PTA.P7;

public class P7_4 {
    public static void main(String[] args) {
        System.out.println("杨辉三角形");
        int n = 10;
        int[][] yangHui = new int[n][n];
        for (int i = 0; i < n; i++) {
            yangHui[i][0] = 1;
            yangHui[i][i] = 1;
            for (int j = 1; j < i; j++) {
                yangHui[i][j] = yangHui[i-1][j-1] + yangHui[i-1][j];
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                System.out.print(yangHui[i][j]+"  ");
            }
            System.out.println();
        }
    }
}

