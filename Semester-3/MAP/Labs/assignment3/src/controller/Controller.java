package controller;

import model.ADTS.*;
import model.PrgState;
import model.exceptions.ExeStackIsEmpty;
import model.exceptions.MyExc;
import model.statements.IStmt;
import model.values.Value;
import repo.IRepository;

import java.io.BufferedReader;

public class Controller {

    IRepository<PrgState> repository;

    public Controller(IRepository<PrgState> repository) {
        this.repository = repository;
    }

    PrgState oneStep(PrgState state, boolean display_flag) throws MyExc {
        MyIStack<IStmt> stk=state.getExeStack();
        if(stk.isEmpty()) throw new ExeStackIsEmpty();
        IStmt crtStmt = stk.pop();
        crtStmt.execute(state);
        if(display_flag) System.out.println(state.toString());
        return state;
    }

    public void allStep(boolean display_flag) throws MyExc {
        PrgState prg = repository.getCrtPrg();
        System.out.println(prg.toString());
        repository.logPrgStateExec();
        while (!prg.getExeStack().isEmpty()){
            oneStep(prg, display_flag);
            repository.logPrgStateExec();
        }
        if(!display_flag) System.out.println(prg.toString());
    }

    public void add(IStmt stmt) throws MyExc{
        PrgState p = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),stmt);
        repository.add(p);
    }
}

