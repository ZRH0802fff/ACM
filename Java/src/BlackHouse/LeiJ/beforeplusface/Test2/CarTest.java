package BlackHouse.LeiJ.beforeplusface.Test2;

import java.util.Scanner;

public class CarTest {
    public static void main(String []args){
        Scanner sc=new Scanner(System.in);
        Car []arr=new Car[3];
        for(int i=0;i<arr.length;i++){
            Car c=new Car();
            String brand=sc.next();
            int money= sc.nextInt();
            String color=sc.next();
            c.setBrand(brand);
            c.setMoney(money);
            c.setColor(color);
            arr[i]=c;
        }
        for(int i=0;i<arr.length;i++){
            Car car=arr[i];
            System.out.println(car.getBrand()+","+car.getMoney()+","+car.getColor());
        }
    }
}
