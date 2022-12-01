package tests;
import controller.Controller;
import model.*;
import repository.IRepository;
import repository.Repository;

public class Tests {
    Controller controller;

    public Tests() {
        IRepository repository = new Repository();
        this.controller = new Controller(repository);
    }

    public void addElems(){
        this.controller.removeAll();
        Entity sare = new Salt(50);
        sare.setPrice(10);
        controller.add(sare);

        Entity zaharBrun = new Sugar("brown");
        zaharBrun.setPrice(30);
        controller.add(zaharBrun);

        Entity zaharAlb = new Sugar("white");
        zaharAlb.setPrice(20);
        controller.add(zaharAlb);

        Entity fainaMalai = new Flour("corn");
        fainaMalai.setPrice(22);
        controller.add(fainaMalai);

        Entity faina000 = new Flour("000");
        faina000.setPrice(10);
        controller.add(faina000);
    }

    public void testEroare(){
        System.out.println("testEroare");
        Entity sareEroare = new Salt(50);
        sareEroare.setPrice(-30);
        controller.add(sareEroare);
        System.out.println("testEroare ok");
    }

    public void testAdd() {
        System.out.println("testAdd");
        addElems();
        Entity[] entities = controller.getAll();

        int count =0;
        for (Entity entity: entities) {
            if(entity != null)
                count+=1;
        }

        System.out.println(count == 5);
        System.out.println("testAdd ok");
    }

    public void testFilter(){
        System.out.println("testFilter");
        addElems();
        Entity[] entities = controller.getAllWithPriceGreaterThan();
        int count =0;
        for (Entity entity: entities) {
            if(entity != null) {
                count += 1;
                System.out.println(entity.getPrice()>=20);
            }
        }
        System.out.println(count == 3);
        System.out.println("testFilter ok");
    }

    public void testRemove(){
        System.out.println("testRemove");
        addElems();
        controller.remove(controller.getAll()[0]);
        Entity[] entities = controller.getAll();
        int count =0;
        for (Entity entity: entities) {
            if(entity != null)
                count+=1;
        }
        System.out.println(count == 4);
        System.out.println("testRemove ok");
    }

    public void testRemoveAll(){
        System.out.println("testRemoveAll");
        addElems();
        controller.removeAll();
        Entity[] entities = controller.getAll();
        int count =0;
        for (Entity entity: entities) {
            if(entity != null)
                count+=1;
        }
        System.out.println(count == 0);
        System.out.println("testRemoveAll ok");
    }

    public void execute(){
        testEroare();
        testAdd();
        testFilter();
        testRemove();
        testRemoveAll();
        System.out.println("\nTests over\n------------------------\n");
    }
}
