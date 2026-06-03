package BlackHouse.LeiJ.String;

import java.util.Scanner;

public class Demo3 {
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        String s=sc.next();
        String f="";
        for(int i=0;i<s.length();i++){
            char c=s.charAt(i);
            String temp=getBig(c);
            f=f+temp;
        }
        int tt=7-s.length();
        for(int i=0;i<tt;i++){
            f="零"+f;
        }
        String[] arr = {"佰","拾","万","仟","佰","拾","元"};
        String ff="";
        for(int i=0;i<7;i++){
            ff=ff+f.charAt(i)+arr[i];
        }
        System.out.println(ff);
    }
    public static String getBig(char c){
        int num=c-'0';
        String[] arr = {"零", "壹", "贰", "叁", "肆", "伍", "陆", "柒", "捌", "玖"};
        return arr[num];
    }
}
