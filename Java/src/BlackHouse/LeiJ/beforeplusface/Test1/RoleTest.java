package BlackHouse.LeiJ.beforeplusface.Test1;

public class RoleTest {
    public static void main(String[] args){
        Role r1=new Role("a",100);
        Role r2=new Role("b",100);
        while (true){
            r1.attack(r2);
            if(r2.getHp()==0) {
                System.out.println(r1.getName() + "KO" + r2.getName());
                break;
            }
            r2.attack(r1);
            if(r1.getHp()==0) {
                System.out.println(r2.getName() + "KO" + r1.getName());
                break;
            }
        }
    }
}
