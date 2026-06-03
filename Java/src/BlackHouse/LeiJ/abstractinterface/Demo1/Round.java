package BlackHouse.LeiJ.abstractinterface.Demo1;

public  class Round extends XingZhuang{
    private double r;

    public Round(double r) {
        this.r = r;
    }

    public Round() {
    }

    public double getR() {
        return r;
    }

    public void setR(double r) {
        this.r = r;
    }

    @Override
    public double s() {
        return r*Math.PI*r;
    }

    @Override
    public double c() {
        return r*Math.PI*2;
    }
}
