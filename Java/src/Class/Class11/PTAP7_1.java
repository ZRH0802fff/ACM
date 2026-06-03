package Class.Class11;
import java.util.Scanner;
public class PTAP7_1 {
    class Product {
        // 私有成员变量
        private String productId;
        private String productName;
        private double productPrice;

        public Product(String productId, String productName, double productPrice) {
            this.productId = productId;
            this.productName = productName;
            this.productPrice = productPrice;
        }

        // Getter和Setter方法
        public String getProductId() {
            return productId;
        }

        public void setProductId(String productId) {
            this.productId = productId;
        }

        public String getProductName() {
            return productName;
        }

        public void setProductName(String productName) {
            this.productName = productName;
        }

        public double getProductPrice() {
            return productPrice;
        }

        public void setProductPrice(double productPrice) {
            this.productPrice = productPrice;
        }

        /**
         * 重写toString方法，按格式返回商品信息
         * 格式：商品编号,商品名称,商品单价
         */
        @Override
        public String toString() {
            return productId + "," + productName + "," + productPrice;
        }
    }
}
