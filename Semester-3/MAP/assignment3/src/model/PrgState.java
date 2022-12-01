package model;

import model.ADTS.MyIDictionary;
import model.ADTS.MyIList;
import model.ADTS.MyIStack;
import model.exceptions.MyExc;
import model.statements.IStmt;
import model.values.Value;

import java.io.BufferedReader;

public class PrgState {
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, Value> symTable;
    MyIList<Value> out;
    MyIDictionary<Value, BufferedReader> fileTable;
    IStmt originalProgram; //optional field, but good to have

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl,
                    MyIList<Value> ot, MyIDictionary<Value, BufferedReader> ft, IStmt prg) throws MyExc {
        exeStack = stk;
        symTable = symtbl;
        out = ot;
        fileTable = ft;
        originalProgram = prg.deepCopy();//recreate the entire original prg
        stk.push(prg);
    }

    public void setFileTable(MyIDictionary<Value, BufferedReader> fileTable) { this.fileTable = fileTable; }

    public MyIDictionary<Value, BufferedReader> getFileTable() { return fileTable; }

    public MyIDictionary<String, Value> getSymTable(){
        return symTable;
    }

    public MyIStack<IStmt> getExeStack(){
        return exeStack;
    }

    public MyIList<Value> getOut(){
        return out;
    }

    public void setExeStack(MyIStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public void setSymTable(MyIDictionary<String, Value> symTable) {
        this.symTable = symTable;
    }

    public void setOut(MyIList<Value> out) {
        this.out = out;
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    public void setOriginalProgram(IStmt originalProgram) {
        this.originalProgram = originalProgram;
    }

    public String toString() {
        return "symbols table: " + symTable.toString() + " | files table: " + fileTable.toString() + " | execution stack(base-top): " + exeStack.toString() + " | output list: " + out.toString();
    }

}
