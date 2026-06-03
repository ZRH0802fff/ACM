package HomeWork;

public class P3_35 {
    public static void main(String[] args){
        int n=1000;
        for(int i=1;i<=1000;i++){
            int fsum=0;
            for(int j=1;j<i;j++){
                if(i%j==0)
                    fsum+=j;
            }
            if(fsum==i)
                System.out.println(i);
        }
    }
}
