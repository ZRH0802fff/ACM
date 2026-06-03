package BlackHouse.LeiJ.String;

import java.util.Scanner;

public class Demo1 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String ru="zs";
        String rp="1234";
        for(int i=0;i<3;i++){
            System.out.println("请输入用户名");
            String u=sc.next();
            System.out.println("请输入密码");
            String p= sc.next();
            if(ru.equals(u)&&rp.equals(p)){
                System.out.println("用户登录成功");
                return;
            }
            else
                System.out.println("失败");
        }
        System.out.println("suo");
    }
}
