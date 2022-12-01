package model.values;

import model.types.Type;
import model.types.IntType;

public class IntValue implements Value {
    int val;
    public IntValue(int v){val=v;}
    @Override
    public Integer getVal() {return val;}
    @Override
    public String toString() { return String.valueOf(val); }
    @Override
    public Type getType() { return new IntType(); }
    @Override
    public Value deepCopy() {
        return new IntValue(val);
    }
    @Override
    public boolean equals(Value another) { return another instanceof IntValue; }
}
