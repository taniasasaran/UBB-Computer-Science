package model.statements;

import model.ADTS.MyIDictionary;
import model.PrgState;
import model.exceptions.FileNotInFileTable;
import model.exceptions.MyExc;
import model.exceptions.VarNotInSymTableError;
import model.exceptions.VarNotOfTypeError;
import model.expressions.Exp;
import model.types.IntType;
import model.types.StringType;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;
import java.io.BufferedReader;
import java.io.IOException;

public class ReadFile implements IStmt{
    String varName;
    Exp exp;
    public ReadFile(String varName, Exp exp) {
        this.varName = varName;
        this.exp = exp;
    }
    @Override
    public PrgState execute(PrgState state) throws MyExc {
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        MyIDictionary<Value, BufferedReader> fileTbl = state.getFileTable();
        if(! symTbl.isDefined(varName)) throw new VarNotInSymTableError(varName);
        if(! symTbl.lookup(varName).getType().equals(new IntType())) throw new VarNotOfTypeError(varName,"int");
        Value ifile = exp.eval(state.getSymTable(), state.getHeap());
        if (!ifile.getType().equals(new StringType()))
            throw new VarNotOfTypeError("file expr","string");
        StringValue file = (StringValue) ifile;
        if(!fileTbl.isDefined(file)) throw new FileNotInFileTable(file);
        BufferedReader buf = null;
        IntValue varValue;
        try {
            buf = fileTbl.lookup(file);
            String read = buf.readLine();
            if(read==null)
                varValue = new IntValue(0);
            else
                varValue = new IntValue(Integer.parseInt(read));
            symTbl.update(varName, varValue);
            return state;
        }
        catch(IOException e){
            throw new MyExc(e.getMessage());
        }
    }
    @Override
    public IStmt deepCopy() { return new ReadFile(varName, exp.deepCopy()); }
    @Override
    public String toString() { return "reading from file "+exp+" into the variable "+varName; }
    public String getVarName() { return varName; }
    public void setVarName(String varName) { this.varName = varName; }
    public Exp getExp() { return exp; }
    public void setExp(Exp exp) { this.exp = exp; }
}
