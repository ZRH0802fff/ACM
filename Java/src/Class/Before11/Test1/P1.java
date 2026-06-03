package Class.Before11.Test1;

public class P1 {
    private String page;
    private String name;
    private  double value;

    public P1() {
    }

    public P1(String page, String name, double value) {
        this.page = page;
        this.name = name;
        this.value = value;
    }

    /**
     * 获取
     * @return page
     */
    public String getPage() {
        return page;
    }

    /**
     * 设置
     * @param page
     */
    public void setPage(String page) {
        this.page = page;
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
     * @return value
     */
    public double getValue() {
        return value;
    }

    /**
     * 设置
     * @param value
     */
    public void setValue(double value) {
        this.value = value;
    }

    public String toString() {
        return "P1{page = " + page + ", name = " + name + ", value = " + value + "}";
    }
}
