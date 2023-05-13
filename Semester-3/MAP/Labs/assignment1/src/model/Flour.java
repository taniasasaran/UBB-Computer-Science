package model;

public class Flour extends Entity {

    private String type;

    public Flour(String type) {
        this.type = type;
    }

    @Override
    public String toString() {
        return "Flour{" +
                "type='" + type + '\'' +
                ", price=" + price +
                '}';
    }
}

