package model.statements;

import model.ADTS.MyIDictionary;
import model.ADTS.MyIHeap;
import model.ADTS.MyIStack;
import model.PrgState;
import model.exceptions.MyExc;
import model.exceptions.MyException;
import model.exceptions.VarAlreadyInSymTable;
import model.types.BoolType;
import model.types.IntType;
import model.types.Type;
import model.values.Value;

public class VarDeclStmt implements IStmt{
    String id;
    Type type;
    public VarDeclStmt(String identifier, Type typ) { id = identifier; type = typ; }
    @Override
    public PrgState execute(PrgState state) throws MyExc {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        if (!symTbl.isDefined(id)) {
            Value defaultValue = type.defaultValue();
            symTbl.add(id, defaultValue);
        } else throw new VarAlreadyInSymTable(id);
        return state;
    }
    @Override
    public IStmt deepCopy() {
        return new VarDeclStmt(id, type.deepCopy());
    }
    @Override
    public String toString() {
        return id + "=(" + type.toString()+")";
    }
}
