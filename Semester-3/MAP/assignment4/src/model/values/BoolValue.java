package model.values;

import model.types.Type;
import model.types.BoolType;

public class BoolValue implements Value {
    boolean val;
    public BoolValue(boolean v){val=v;}
    @Override
    public Boolean getVal() {return val;}
    @Override
    public String toString() { return String.valueOf(val); }
    @Override
    public Value deepCopy() {
        return new BoolValue(val);
    }
    @Override
    public Type getType() { return new BoolType(); }
    @Override
    public boolean equals(Value another) { return another instanceof BoolValue; }
}