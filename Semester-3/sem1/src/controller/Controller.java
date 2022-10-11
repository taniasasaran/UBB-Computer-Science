package controller;

import exceptions.NegativeWeightExceptions;
import model.Entity;
import repository.IRepository;

import java.util.List;

public class Controller {

    IRepository repostory;

    public Controller(IRepository repository) {
        this.repostory = repository;
    }

    public void add(Entity entity) {
        try {
            repostory.add(entity);
        } catch (NegativeWeightExceptions e) {
            System.out.println("Negative weight error!!");
        }
    }

    public void remove(Entity entity) {
        repostory.remove(entity);
    }

    public Entity[] getAll() {
        return repostory.getAll();
    }

    public List<Entity> getAllWithWeightGreaterThan200() {
        return repostory.getAllWithWeightGreaterThan200();
    }
}
