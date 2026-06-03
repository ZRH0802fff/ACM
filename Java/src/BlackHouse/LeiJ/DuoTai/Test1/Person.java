package BlackHouse.LeiJ.DuoTai.Test1;

public class Person {
    private String name;
    private int age;

    public Person() {
    }

    public Person(String name, int age) {
        this.name = name;
        this.age = age;
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
     * @return age
     */
    public int getAge() {
        return age;
    }

    /**
     * 设置
     * @param age
     */
    public void setAge(int age) {
        this.age = age;
    }

    public String toString() {
        return "Person{name = " + name + ", age = " + age + "}";
    }

    public void keepPet(Animal a,String food){
        if(a instanceof Dog) {
            Dog d =(Dog) a;
            System.out.println("年龄为" + age + "岁的" + name +
                    "养了一只" + a.getColoar() + "颜色的" + a.getName() + "岁的狗");
            d.eat(food);
        }else if (a instanceof Cat){
            Cat c=(Cat) a;
            System.out.println("年龄为" + age + "岁的" + name +
                    "养了一只" + c.getColoar() + "颜色的" + c.getName() + "岁的猫");
            c.eat(food);
        }else{
            System.out.println("没有这种动物");
        }
    }
}
