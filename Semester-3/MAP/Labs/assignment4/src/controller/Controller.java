package controller;

import model.ADTS.*;
import model.PrgState;
import model.exceptions.ExeStackIsEmpty;
import model.exceptions.MyExc;
import model.statements.IStmt;
import model.values.RefValue;
import model.values.Value;
import repo.IRepository;

import java.io.BufferedReader;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller {

    IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    Map<Integer,Value> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer,Value> heapAddr){
        return heapAddr.entrySet().stream()
                .filter(elem-> symTableAddr.contains(elem.getKey()) || heapAddr.containsKey(elem.getKey()))
                .collect(Collectors.toMap(HashMap.Entry::getKey, HashMap.Entry::getValue)); }

    List<Integer> getAddrFromSymTable(Collection<Value> symTableValues){
        return symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue)v; return v1.getVal();})
                .collect(Collectors.toList()); }

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
            prg.getHeap().setContent((HashMap<Integer, Value>) safeGarbageCollector(
                    getAddrFromSymTable(prg.getSymTable().getDict().values()),
                    prg.getHeap().getContent()));
        }
        if(!display_flag) System.out.println(prg.toString());
    }
}

