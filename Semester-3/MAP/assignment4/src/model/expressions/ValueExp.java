package model.expressions;

import model.ADTS.MyIDictionary;
import model.ADTS.MyIHeap;
import model.values.Value;

public class ValueExp implements Exp {
    Value e;
    public ValueExp(Value v) { e = v; }
    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer, Value> hp){
        return e;
    }
    @Override
    public Exp deepCopy() {
        return new ValueExp(e.deepCopy());
    }

    @Override
    public String toString(){ return e.toString();}
}
