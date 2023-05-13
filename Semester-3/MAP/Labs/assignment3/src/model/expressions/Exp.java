package model.expressions;

import model.ADTS.MyIDictionary;
import model.exceptions.DivisionByZeroException;
import model.exceptions.Exc;
import model.exceptions.MyExc;
import model.exceptions.MyException;
import model.values.Value;

public interface Exp {
    Value eval(MyIDictionary<String,Value> tbl) throws MyExc;
    Exp deepCopy();
    String toString();
}
