package model;

public class Cake extends Entity {

    private String flavour;

    public Cake(String flavour) {
        this.flavour = flavour;
    }

    @Override
    public String toString() {
        return "Cake{" +
                "flavour='" + flavour + '\'' +
                ", weight=" + weight +
                '}';
    }
}
