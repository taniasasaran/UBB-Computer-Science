package model.statements;

import model.ADTS.MyIStack;
import model.PrgState;
import model.exceptions.MyExc;
import model.exceptions.MyException;

public class CompStmt implements IStmt
{
    IStmt first;
    IStmt second;
    public CompStmt(IStmt stmt1, IStmt stmt2) { first = stmt1; second = stmt2;}
    @Override
    public String toString()
    {
        return "("+first.toString() + ";" + second.toString()+")";
    }
    @Override
    public PrgState execute(PrgState state)  throws MyExc {
        MyIStack<IStmt> stk=state.getExeStack();
        stk.push(second);
        stk.push(first);
        return state;
    }
    @Override
    public IStmt deepCopy() {
        return new CompStmt(first.deepCopy(), second.deepCopy());
    }
}
