package model.expressions;

import model.ADTS.MyIDictionary;
import model.ADTS.MyIHeap;
import model.exceptions.MyExc;
import model.exceptions.VarNotOfTypeError;
import model.types.BoolType;
import model.values.BoolValue;
import model.values.Value;

public class LogicExp implements Exp{
    Exp e1;
    Exp e2;
    int op; // 1and 2or

    LogicExp(Exp exp1, Exp exp2, int operator) { e1=exp1; e2=exp2; op=operator;}
    @Override
    public Value eval(MyIDictionary<String, Value> tbl, MyIHeap<Integer, Value> hp) throws MyExc {
        Value v1;
        Value v2;
        v1 = e1.eval(tbl,hp);
        if (v1.getType().equals(new BoolType())) {
            v2 = e2.eval(tbl,hp);
            if (v2.getType().equals(new BoolType())) {
                BoolValue b1 = (BoolValue) v1;
                BoolValue b2 = (BoolValue) v2;
                return new BoolValue(evalBool(b1, b2, op));
            } else
                throw new VarNotOfTypeError("second operand", "boolean");
        } else
            throw new VarNotOfTypeError("first operand", "boolean");
    }

    @Override
    public String toString(){
        if (op == 1) return e1.toString()+" and "+e2.toString();
        if (op == 2) return e1.toString()+" or "+e2.toString();
        return null;
    }

    public boolean evalBool(BoolValue v1, BoolValue v2, int op) throws MyExc{
        if(op == 1) return (v1.getVal() && v2.getVal());
        else if(op == 2) return (v1.getVal() || v2.getVal());
        else throw new MyExc("operator not supported");
    }

    @Override
    public Exp deepCopy() {
        return new RelationalExp(e1.deepCopy(), e2.deepCopy(),op);
    }
}