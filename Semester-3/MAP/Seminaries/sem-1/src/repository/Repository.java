package repository;

import exceptions.NegativeWeightExceptions;
import model.Entity;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {

    private Entity[] entities;

    private int size;

    public Repository() {
        entities = new Entity[100];
        size = 0;
    }

    @Override
    public void add(Entity entity) throws NegativeWeightExceptions {
        if (entity.getWeight() <= 0) {
            throw new NegativeWeightExceptions();
        }
        entities[size] = entity;
        size++;
    }

    @Override
    public void remove(Entity entity) {

    }

    @Override
    public Entity[] getAll() {
        return entities;
    }

    @Override
    public List<Entity> getAllWithWeightGreaterThan() {
        List<Entity> filterEntities = new ArrayList<>();

        for (int index = 0; index < size; index++) {
            Entity entity = entities[index];
            if (entity.getWeight() >= 200)
                filterEntities.add(entity);
        }
        return filterEntities;
    }
}
