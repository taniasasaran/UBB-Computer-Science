package view;

import controller.Controller;
import model.*;

//import java.util.List;

public class View {

    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void execute() {
        Entity sare = new Salt(50);
        sare.setPrice(10);
        controller.add(sare);

        Entity sareEroare = new Salt(50);
        sareEroare.setPrice(-30);
        controller.add(sareEroare);

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

        Entity[] entities = controller.getAllWithPriceGreaterThan();

        for (Entity entity: entities) {
            if(entity != null)
                System.out.println(entity);
        }
        System.out.println("\n------------------------\n");
        for (Entity entity: controller.getAll()) {
            if(entity != null)
                System.out.println(entity);
        }
    }
}
