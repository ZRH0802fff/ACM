package BlackHouse.LeiJ.beforeplusface.Test1;

import java.util.Random;

public class Role {
    private String name;
    private int hp;

    public Role() {
    }

    public Role(String name, int hp) {
        this.name = name;
        this.hp = hp;
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
     * @return hp
     */
    public int getHp() {
        return hp;
    }

    /**
     * 设置
     * @param hp
     */
    public void setHp(int hp) {
        this.hp = hp;
    }

    public String toString() {
        return "Role{name = " + name + ", hp = " + hp + "}";
    }
    public void attack(Role role){
        Random r=new Random();
        int hurt=r.nextInt(20)+1;
        int yuhp= role.getHp()-hurt;
        yuhp=yuhp<0?0:yuhp;
        role.setHp(yuhp);
        System.out.println(this.getName()+"打"+role.getName()+"，造成"+hurt+"伤害。剩余"+yuhp+"点血");
    }
}
