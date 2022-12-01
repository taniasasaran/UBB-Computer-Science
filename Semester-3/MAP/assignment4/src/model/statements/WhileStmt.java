package model.statements;

import model.PrgState;
import model.exceptions.MyExc;
import model.exceptions.VarNotOfTypeError;
import model.expressions.Exp;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public class WhileStmt implements IStmt{
    Exp exp;
    IStmt repeatStmt;
    public WhileStmt(Exp e, IStmt t) {exp=e; repeatStmt =t;}
    @Override
    public String toString(){ return "(WHILE("+ exp.toString()+") " + repeatStmt.toString()+")";}

    @Override
    public PrgState execute(PrgState state) throws MyExc {
        Value icondition = exp.eval(state.getSymTable(), state.getHeap());
        if (!icondition.getType().equals(new BoolType()))
            throw new VarNotOfTypeError("conditional expr","boolean");
        BoolValue condition = (BoolValue) icondition;
        if(condition.getVal()) {
            state.getExeStack().push(this);
            state.getExeStack().push(repeatStmt);
        }
        return state;
    }
    @Override
    public IStmt deepCopy() {
        return new WhileStmt(exp.deepCopy(), repeatStmt.deepCopy());
    }
}
