package HomeWork.PTA.P8;

import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        Pupil zhangsan=new Pupil();
        String s = sc.next();
        zhangsan.setSchool(s);
        System.out.println("我的学校是"+zhangsan.getSchool());
        zhangsan.breath();
        zhangsan.eat();
        zhangsan.sleep();
        zhangsan.think();
    }
}
