package model.statements;


import model.PrgState;
import model.exceptions.MyExc;
import model.expressions.Exp;
import model.values.Value;

public class PrintStmt implements IStmt{
    Exp exp;
    public PrintStmt(Exp expression) { exp = expression; }
    @Override
    public String toString(){ return "print(" +exp.toString()+")";}
    @Override
    public PrgState execute(PrgState state) throws MyExc {
        Value print = exp.eval(state.getSymTable(), state.getHeap());
        state.getOut().add(print);
        return state;
    }
    @Override
    public IStmt deepCopy() {
        return new PrintStmt(exp.deepCopy());
    }
}
