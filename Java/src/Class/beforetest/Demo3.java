package Class.beforetest;

import java.util.ArrayList;

public class Demo3{
    public static void main(String[] args) {
        ArrayList<Integer> array=new ArrayList<Integer>();
        array.add(1);
        array.add(3);
        System.out.println(array);
        System.out.println(array.remove("1"));
        System.out.println(array);
        System.out.println(array.set(0,2));
        System.out.println(array);
        System.out.println(array.get(0));
        System.out.println(array.size());
    }
}
