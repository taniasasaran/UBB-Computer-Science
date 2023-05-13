package model.expressions;

import model.ADTS.MyIDictionary;
import model.ADTS.MyIHeap;
import model.exceptions.MyExc;
import model.exceptions.VarNotInSymTableError;
import model.values.Value;

public class VarExp implements Exp{
    String id;
    public VarExp(String vid) { id = vid; }
    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer, Value> hp) throws MyExc {
        if(!tbl.containsKey(id))
            throw new VarNotInSymTableError(id);
        return tbl.lookup(id);    }
    @Override
    public Exp deepCopy() {
        return new VarExp(id);
    }

    @Override
    public String toString(){ return id;}
}
