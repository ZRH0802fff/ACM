package Class.Class12;

public abstract class anm {
    String name;
    int age;

    public anm() {
    }

    public anm(String name, int age) {
        this.name = name;
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
    public abstract void eat();
    public void drink(){
        System.out.println("喝水");
    }
}
