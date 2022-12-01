package repository;

import exceptions.NegativePriceExceptions;
import model.Entity;

import java.util.List;

public interface IRepository {

    void add(Entity entity) throws NegativePriceExceptions;

    void remove(Entity entity);

    Entity[] getAll();

    Entity[] getAllWithPriceGreaterThan() ;

    int getSize();
}
