import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ExtendedProduct extends Product {
    private final Lock mutex;
    private int soldQuantity;

    public ExtendedProduct(String name, int price, int quantity) {
        super(name, quantity, price);
        this.mutex = new ReentrantLock(true);
        this.soldQuantity = 0;
    }

    public int getSoldQuantity() { return soldQuantity; }
    public Lock getMutex() { return mutex; }
    public void setSoldQuantity(int soldQuantity) { this.soldQuantity = soldQuantity; }
}