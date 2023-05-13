package repository;

import exceptions.NegativeWeightExceptions;
import model.Entity;

import java.util.List;

public interface IRepository {

    void add(Entity entity) throws NegativeWeightExceptions;

    void remove(Entity entity);

    Entity[] getAll();

    List<Entity> getAllWithWeightGreaterThan() ;
}
