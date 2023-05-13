package repo;

import model.ADTS.MyIList;
import model.exceptions.MyExc;

public interface IRepository<T> {

    int getSize();
    void add(T entity) throws MyExc;

    void remove(T entity) throws MyExc;
    void logPrgStateExec() throws MyExc;
    T getCrtPrg() throws MyExc;
    MyIList<T> getAll();
}
