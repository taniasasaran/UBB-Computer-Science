package model.statements;

import model.PrgState;
import model.exceptions.MyExc;
import model.exceptions.VarNotOfTypeError;
import model.expressions.Exp;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public class IfStmt implements IStmt{
    Exp exp;
    IStmt thenS;
    IStmt elseS;
    public IfStmt(Exp e, IStmt t, IStmt el) {exp=e; thenS=t;elseS=el;}
    @Override
    public String toString(){ return "(IF("+ exp.toString()+") THEN(" +thenS.toString() +")ELSE("+elseS.toString()+"))";}

    @Override
    public PrgState execute(PrgState state) throws MyExc {
        Value icondition = exp.eval(state.getSymTable(), state.getHeap());
        if (!icondition.getType().equals(new BoolType()))
            throw new VarNotOfTypeError("conditional expr","boolean");
        BoolValue condition = (BoolValue) icondition;
        if(condition.getVal())  state.getExeStack().push(thenS);
        else  state.getExeStack().push(elseS);
        return state;
    }
    @Override
    public IStmt deepCopy() {
        return new IfStmt(exp.deepCopy(),thenS.deepCopy(), elseS.deepCopy());
    }
}
