package model.statements;

import model.ADTS.MyIDictionary;
import model.ADTS.MyIHeap;
import model.ADTS.MyIStack;
import model.PrgState;
import model.exceptions.*;
import model.expressions.Exp;
import model.types.Type;
import model.values.Value;

public class AssignStmt implements IStmt {
    String id;
    Exp exp;

    public AssignStmt(String identifier, Exp expression) {id = identifier; exp = expression;}

    @Override
    public String toString() {
        return id + "=" + exp.toString();
    }
    @Override
    public PrgState execute(PrgState state) throws MyExc {
        MyIStack<IStmt> stk = state.getExeStack();
        MyIHeap<Integer, Value> hp = state.getHeap();
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        if (symTbl.isDefined(id)) {
            Value val = exp.eval(symTbl,hp);
            Type typId = (symTbl.lookup(id)).getType();
            if ((val.getType()).equals(typId))
                symTbl.update(id, val);
            else
                throw new VariableAndTypeDoNotMatch(id);
        } else throw new VarNotInSymTableError(id);
        return state;
    }

    @Override
    public IStmt deepCopy() {
        return new AssignStmt(id, exp.deepCopy());
    }
}

