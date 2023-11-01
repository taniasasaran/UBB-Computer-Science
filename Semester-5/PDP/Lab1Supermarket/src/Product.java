public class Product {
    private final String name;
    private int quantity;
    private final int price;

    public Product(String name, int quantity, int price) {
        this.name = name;
        this.quantity = quantity;
        this.price = price;
    }

    public String getName() { return name; }
    public int getQuantity() { return quantity; }
    public int getPrice() { return price; }
    public void setQuantity(int quantity) { this.quantity = quantity; }
}