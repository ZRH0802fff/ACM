package BlackHouse.LeiJ.beforeplusface.Test3;

public class Phone {
    private String brand;
    private int value;
    private String color;

    public Phone() {
    }

    public Phone(String brand, int value, String color) {
        this.brand = brand;
        this.value = value;
        this.color = color;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }
}
