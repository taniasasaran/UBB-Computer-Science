package view;

import controller.Controller;
import model.Apple;
import model.Book;
import model.Cake;
import model.Entity;

import java.util.List;

public class View {

    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void execute() {
        Entity book = new Book(150, "It Ends With Us");
        book.setWeight(150);
        controller.add(book);

        Entity apple = new Apple("yellow");
        apple.setWeight(300);
        controller.add(apple);

        Entity cake = new Cake("chocolate");
        cake.setWeight(1200);
        controller.add(cake);

        Entity cakeException = new Cake("vanilla");
        cakeException.setWeight(-300);
        controller.add(cakeException);

        List<Entity> repoFiltered = controller.getAllWithWeightGreaterThan200();

        for (Entity entity: repoFiltered) {
            System.out.println(entity);
        }
    }
}
