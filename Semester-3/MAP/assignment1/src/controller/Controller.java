package controller;

import exceptions.NegativePriceExceptions;
import model.Entity;
import repository.IRepository;

public class Controller {

    IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void add(Entity entity) {
        try {
            repository.add(entity);
        } catch (NegativePriceExceptions e) {
            System.out.println("Negative price error!!");
        }
    }

    public void remove(Entity entity) {
        repository.remove(entity);
    }

    public void removeAll(){
        while(repository.getSize()>0)
            for(Entity entity: repository.getAll()) {
                if (entity != null)
                    repository.remove(entity);
                if(entity == null)
                    break;
            }
    }

    public Entity[] getAll() {
        return repository.getAll();
    }

    public Entity[] getAllWithPriceGreaterThan() {
        return repository.getAllWithPriceGreaterThan();
    }
}
