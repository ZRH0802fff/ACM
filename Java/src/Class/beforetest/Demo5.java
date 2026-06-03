package Class.beforetest;

import java.util.HashMap;
import java.util.Map;

public class Demo5 {
    public static void main(String[] args) {
        Map<String,String> m=new HashMap<>();
        m.put("郭靖", "黄蓉");
        m.put("韦小宝","沐剑屏");
        m.put("尹志平","小龙女");
        //String value2 = m.put("韦小宝", "双儿");
        //System.out.println(value2);
        //删除
        String result = m.remove("郭靖");//黄蓉
        System.out.println(result);
    }
}
