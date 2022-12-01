package model.statements;

import model.ADTS.MyIDictionary;
import model.PrgState;
import model.exceptions.FileAlreadyInFileTable;
import model.exceptions.MyExc;
import model.exceptions.VarAlreadyInSymTable;
import model.exceptions.VarNotOfTypeError;
import model.expressions.Exp;
import model.types.StringType;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.InputStreamReader;

public class openRFile implements IStmt{
    Exp exp;

    public openRFile(Exp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyExc {
        Value ifile = exp.eval(state.getSymTable());
        if (!ifile.getType().equals(new StringType()))
            throw new VarNotOfTypeError("file expr","string");
        StringValue file = (StringValue) ifile;
        MyIDictionary<Value, BufferedReader> fileTbl = state.getFileTable();
        if (fileTbl.isDefined(file)) throw new FileAlreadyInFileTable(file);
        BufferedReader buf = null; //TODO: check with rares
        try{
            FileReader fd = new FileReader(file.getVal());
            buf = new BufferedReader(fd);
            fileTbl.add(ifile,buf);
            return state;
        } catch (FileNotFoundException e) {
            throw new MyExc(e.getMessage());
        }
    }

    @Override
    public IStmt deepCopy() { return new openRFile(exp.deepCopy()); }
    @Override
    public String toString(){
        return "open "+exp;
    }

}
