package repository;

import exceptions.NegativePriceExceptions;
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

    public int getSize(){return size;}

    @Override
    public void add(Entity entity) throws NegativePriceExceptions {
        if (entity.getPrice() <= 0) {
            throw new NegativePriceExceptions();
        }
        entities[size] = entity;
        size++;
    }

    @Override
    public void remove(Entity entity) {
        for (int index=0; index<size; index++) {
            Entity ent = entities[index];
            if (entity == ent){
                entities[index] = entities[size-1];
                entities[size-1] = null;
                size-=1;
            }
        }
    }

    @Override
    public Entity[] getAll() {
        return entities;
    }


    @Override
    public Entity[] getAllWithPriceGreaterThan() {
        Entity[] filterEntities = new Entity[100];
        int filterSize = 0;
        for (int index = 0; index < size; index++) {
            Entity entity = entities[index];
            if (entity.getPrice() >= 20) {
                filterEntities[filterSize] = entity;
                filterSize+=1;
            }
        }
        return filterEntities;
    }
}
