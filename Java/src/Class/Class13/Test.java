package Class.Class13;

public class Test {
    public static void main(String[] args) {

                USB usb1 = new Mouse();
                usb1.work();
                usb1.stop();

                USB[] usbs = new USB[2];
                usbs[0] = new UPan();
                usbs[1] = new Mouse();

                for (int i = 0; i < usbs.length; i++) {
                    usbs[i].work();
                    usbs[i].stop();
                }
    }
}
