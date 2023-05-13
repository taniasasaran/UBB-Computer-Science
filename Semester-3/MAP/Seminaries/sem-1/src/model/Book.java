package model;

public class Book extends Entity {

    private int noPages;
    private String title;

    public Book(int noPages, String title) {
        this.noPages = noPages;
        this.title = title;
    }

    @Override
    public String toString() {
        return "Book{" +
                "noPages=" + noPages +
                ", title='" + title + '\'' +
                ", weight=" + weight +
                '}';
    }
}
