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
        Entity apple = new Apple("red");
        apple.setWeight(500);
        controller.add(apple);

        Entity book = new Book(50, "Double quotes");
        book.setWeight(100);
        controller.add(book);

        Entity cake = new Cake("mango");
        cake.setWeight(2000);
        controller.add(cake);

        Entity book2 = new Book(100, "Single quotes");
        book2.setWeight(-2000);
        controller.add(book2);

        List<Entity> entities = controller.getAllWithWeightGreaterThan();

        for (Entity entity: entities) {
            System.out.println(entity);
        }
    }
}
