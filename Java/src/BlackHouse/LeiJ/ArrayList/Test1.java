package BlackHouse.LeiJ.ArrayList;

import java.util.ArrayList;

public class Test1 {
    public static void main(String[] args) {
        Phone p1=new Phone("mi",1000);
        Phone p2=new Phone("p",8000);
        Phone p3=new Phone("t",2999);
        ArrayList<Phone>list=new ArrayList<>();
        list.add(p1);
        list.add(p2);
        list.add(p3);
        ArrayList<Phone>flist=check(list);
        System.out.println(flist);
    }
    public static ArrayList<Phone> check(ArrayList<Phone> list){
        ArrayList<Phone>flist=new ArrayList<>();
        for (int i = 0; i < list.size(); i++) {
            Phone p=list.get(i);
            if(p.getValue()<3000)
                flist.add(p);
        }
        return flist;
    }
}
