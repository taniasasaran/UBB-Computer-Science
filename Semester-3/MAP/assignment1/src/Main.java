import controller.Controller;
import repository.IRepository;
import repository.Repository;
import tests.Tests;
import view.View;

public class Main {
    public static void main(String[] args) {
        IRepository repository = new Repository();
        Controller controller = new Controller(repository);
        View view = new View(controller);
        Tests tests = new Tests();
        tests.execute();
        view.execute();
    }
}





































