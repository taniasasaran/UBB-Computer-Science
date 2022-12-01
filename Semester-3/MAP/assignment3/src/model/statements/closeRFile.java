package model.statements;

import model.ADTS.MyIDictionary;
import model.PrgState;
import model.exceptions.FileAlreadyInFileTable;
import model.exceptions.FileNotInFileTable;
import model.exceptions.MyExc;
import model.exceptions.VarNotOfTypeError;
import model.expressions.Exp;
import model.types.StringType;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class closeRFile implements IStmt{
    Exp exp;
    public closeRFile(Exp exp) { this.exp = exp; }
    @Override
    public PrgState execute(PrgState state) throws MyExc {
        Value ifile = exp.eval(state.getSymTable());
        if (!ifile.getType().equals(new StringType()))
            throw new VarNotOfTypeError("close expr","string");
        StringValue file = (StringValue) ifile;
        MyIDictionary<Value, BufferedReader> fileTbl = state.getFileTable();
        if (!fileTbl.isDefined(file)) throw new FileNotInFileTable(file);
        try{
            fileTbl.lookup(ifile).close();
            fileTbl.remove(ifile);
            return state;
        } catch (IOException e) {
            throw new MyExc(e.getMessage());
        }
    }

    @Override
    public IStmt deepCopy() { return new closeRFile(exp.deepCopy()); }

    public Exp getExp() { return exp; }

    public void setExp(Exp exp) { this.exp = exp; }

    @Override
    public String toString() { return "closing the file "+exp; }
}
