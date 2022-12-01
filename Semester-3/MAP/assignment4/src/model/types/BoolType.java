package model.types;

import model.values.BoolValue;

public class BoolType implements Type {
    @Override
    public boolean equals(Object another) {
        return another instanceof BoolType;
    }
    @Override
    public String toString() {
        return "bool";
    }
    @Override
    public BoolValue defaultValue() {return new BoolValue(false);}

    @Override
    public Type deepCopy() {
        return new BoolType();
    }
}
