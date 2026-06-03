package BlackHouse.LeiJ.ArrayList;

import java.util.ArrayList;

public class Demo2 {
    public static void main(String[] args) {
        ArrayList<String> list =new ArrayList<>();
        boolean f1= list.add("aaa");
        boolean f2 = list.add("bbb");
        boolean f3 = list.add("ccc");
        for (int i = 0; i < list.size(); i++) {
            String s = list.get(i);
            System.out.println(s);
        }
    }
}
