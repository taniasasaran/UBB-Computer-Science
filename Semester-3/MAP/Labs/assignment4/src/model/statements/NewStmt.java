package model.statements;

import model.PrgState;
import model.exceptions.MyExc;
import model.expressions.Exp;
import model.types.RefType;
import model.values.RefValue;
import model.values.Value;

import java.util.Objects;

public class NewStmt implements IStmt {
    private String varName;
    private Exp expression;

    public NewStmt(String varName, Exp exp) {
        this.varName = varName;
        this.expression = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyExc {
        if(!state.getSymTable().isDefined(varName))
            throw new MyExc("Variable not defined");
        if(Objects.equals(state.getSymTable().lookup(varName).getType().toString(), "RefType"))
            throw new MyExc("Variable is not an reference type");
        Value val = expression.eval(state.getSymTable(), state.getHeap());
        if(!Objects.equals(((RefType) state.getSymTable().lookup(varName).getType()).getInner(), val.getType()))
            throw new MyExc("Variable type and expression type do not match(new)");
        int address = state.getHeap().getFree();
        state.getHeap().add(address, val);
        state.getSymTable().add(varName, new RefValue(address, val.getType()));
        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new NewStmt(varName, expression);
    }

    @Override
    public String toString() {
        return "new(" +
                "varName='" + varName + '\'' +
                ", expression='" + expression.toString() + '\'' +
                ')';
    }
}

