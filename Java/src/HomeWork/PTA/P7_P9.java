package HomeWork.PTA;

public class P7_P9 {
    public static void main(String[] args) {
        String str = "    abc d123";
        str.toUpperCase();
        String s2=str.trim();
        System.out.println(s2);
        StringBuffer sb = new StringBuffer("Hello");
        sb.insert(4, " World");   // "Hello World"
        //sb.insert(0, "Start: ");  // "Start: Hello World"
        //sb.insert(7, 123);        // "Start: 123Hello World"
        System.out.println(sb);
    }
}
