package model.values;

import model.types.RefType;
import model.types.Type;

public class RefValue implements Value{
    int address;
    Type locationType;
    public RefValue(int addr, Type location) { address = addr; locationType = location; }
    @Override
    public Type getType() { return new RefType(locationType);}

    @Override
    public Integer getVal() { return address; }

    @Override
    public Value deepCopy() {
        return null;
    }

    @Override
    public boolean equals(Value another) {
        return false;
    }

    public String toString() { return "("+address+", "+locationType.toString()+")"; }
}
