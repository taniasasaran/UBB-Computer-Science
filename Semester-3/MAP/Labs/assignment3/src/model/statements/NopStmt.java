package model.statements;

import model.PrgState;

public class NopStmt implements IStmt{
    NopStmt(){}
    @Override
    public PrgState execute(PrgState state) {
        return state;
    }
    @Override
    public IStmt deepCopy() {
        return new NopStmt();
    }
    @Override
    public String toString() { return "no operation statement";}
}
