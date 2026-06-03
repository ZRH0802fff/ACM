package BlackHouse.LeiJ.abstractinterface.Demo1;

public class Rectangle extends XingZhuang{

    private int l;
    private int k;

    public Rectangle() {
    }

    public Rectangle(int k, int l) {
        this.k = k;
        this.l = l;
    }

    public int getK() {
        return k;
    }

    public void setK(int k) {
        this.k = k;
    }

    public int getL() {
        return l;
    }

    public void setL(int l) {
        this.l = l;
    }

    @Override
    public double s() {
        return l*k;
    }

    @Override
    public double c() {
        return l+l+k+k;
    }
}
