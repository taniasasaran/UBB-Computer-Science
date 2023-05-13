package model;

public class Salt extends Entity {

    private int quantity;

    public Salt(int quantity) {
        this.quantity = quantity;
    }

    @Override
    public String toString() {
        return "Salt{" +
                "quantity='" + quantity + '\'' +
                ", price=" + price +
                '}';
    }
}
