package BlackHouse.LeiJ.YIchang;

import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        Scanner sc =new Scanner(System.in );
        GirlFriend a1=new GirlFriend();
        while(true){
            try {
                System.out.println("请输入你心仪的女朋友的名字");
                String name=sc.nextLine();
                a1.setName(name);
                System.out.println("请输入你心仪的女朋友的年龄");
                String ageStr=sc.nextLine();
                int age = Integer.parseInt(ageStr);
                a1.setAge(age);
                break;
            } catch (NumberFormatException e) {
                System.out.println("年龄的格式有误，请输入数字");
            } catch (RuntimeException e){
                System.out.println("姓名的长度或者年龄的范围有误");
            }
        }
        System.out.println(a1);
    }
}
