package BlackHouse.LeiJ.abstractinterface.demo2;

public class NewPhone extends Phone implements Play {
    @Override
    public void playgame() {
        System.out.println("新手机打游戏");
    }
}
