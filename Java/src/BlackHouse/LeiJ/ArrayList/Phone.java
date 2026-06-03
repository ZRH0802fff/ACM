package BlackHouse.LeiJ.ArrayList;

public class Phone {
    private String brand;
    private int value;

    public Phone() {
    }

    public Phone(String brand, int value) {
        this.brand = brand;
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }
    @Override
    public String toString() {
        return "Phone{brand='" + brand + "', value=" + value + "}";
    }
}
