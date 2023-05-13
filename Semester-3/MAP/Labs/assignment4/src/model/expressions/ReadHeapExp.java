package model.expressions;

import model.ADTS.MyIDictionary;
import model.ADTS.MyIHeap;
import model.exceptions.MyExc;
import model.values.RefValue;
import model.values.Value;

import java.util.Objects;

public class ReadHeapExp implements Exp {
    private Exp expression;

    public ReadHeapExp(Exp exp) {
        this.expression = exp;
    }

    @Override
    public Value eval(MyIDictionary<String,Value> tbl, MyIHeap<Integer, Value> hp) throws MyExc {
        Value val = expression.eval(tbl, hp);
        String s =val.getType().toString();
        if (val.getType().toString().matches("Ref")) {
            throw new MyExc("Expression is not a reference value");
        }
        RefValue ref = (RefValue) val;
        if (!hp.isDefined(ref.getVal())) {
            throw new MyExc("Address is not defined in the heap");
        }
        return hp.lookup(ref.getVal());
    }

    @Override
    public Exp deepCopy() {
        return new ReadHeapExp(expression);
    }

    @Override
    public String toString() { return "readHeap(" + "varName='" + expression + '\'' + ')'; }
}
