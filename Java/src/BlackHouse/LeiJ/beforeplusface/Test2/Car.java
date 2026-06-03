package BlackHouse.LeiJ.beforeplusface.Test2;

public class Car {
    private String brand;
    private int money;
    private String color;

    public Car() {
    }

    public Car(String brand, int money, String color) {
        this.brand = brand;
        this.money = money;
        this.color = color;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public int getMoney() {
        return money;
    }

    public void setMoney(int money) {
        this.money = money;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }
}
