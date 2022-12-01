package model.types;

import model.values.IntValue;

public class IntType implements Type {
    public IntType() {}
    @Override
    public boolean equals(Object another) {
        return another instanceof IntType;
    }
    @Override
    public String toString() {
        return "int";
    }
    @Override
    public IntValue defaultValue() {return new IntValue(0);}

    @Override
    public Type deepCopy() {
        return new IntType();
    }
}