package repo;

import model.ADTS.MyIList;
import model.PrgState;
import model.exceptions.MyExc;
import model.statements.IStmt;

public interface IRepository {

    int getSize();
    void add(PrgState entity) throws MyExc;

    void remove(PrgState entity) throws MyExc;
    void logPrgStateExec() throws MyExc;
    PrgState getCrtPrg() throws MyExc;
    MyIList<PrgState> getAll();
}
