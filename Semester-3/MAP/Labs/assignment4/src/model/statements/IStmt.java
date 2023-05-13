package model.statements;

import model.PrgState;
import model.exceptions.MyExc;

public interface  IStmt{
    PrgState execute(PrgState state) throws MyExc;       //which is the execution method for a statement.
    IStmt deepCopy();
    String toString();
}
