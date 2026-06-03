package BlackHouse.LeiJ.API_Math;

public class Test1 {
    public static void main(String[] args) {
        int []a=new int[3];
        int []b=new int[]{1,2,3,4,5};
        a=b;
        for (int i = 0; i < b.length; i++) {
            System.out.print(a[i]+" ");
        }
    }
}
