package model;

public class Sugar extends Entity {

    private String color;

    public Sugar(String color) {
        this.color = color;
    }

    @Override
    public String toString() {
        return "Sugar{" +
                "color='" + color + '\'' +
                ", price=" + price +
                '}';
    }
}

