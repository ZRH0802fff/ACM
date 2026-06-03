package BlackHouse.LeiJ.DuoTai.Test1;

public class Animal {
    private String name;
    private String coloar;


    public Animal() {
    }

    public Animal(String name, String coloar) {
        this.name = name;
        this.coloar = coloar;
    }

    /**
     * 获取
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * 设置
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * 获取
     * @return coloar
     */
    public String getColoar() {
        return coloar;
    }

    /**
     * 设置
     * @param coloar
     */
    public void setColoar(String coloar) {
        this.coloar = coloar;
    }

    public String toString() {
        return "Animal{name = " + name + ", coloar = " + coloar + "}";
    }

    public void eat(String food){
        System.out.println("动物在吃" + food );
    }
}
