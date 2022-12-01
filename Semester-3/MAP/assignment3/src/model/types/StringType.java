package model.types;

import model.values.StringValue;

public class StringType implements Type {
    @Override
    public boolean equals(Object another) {
        return another instanceof StringType;
    }
    @Override
    public String toString() {
        return "string";
    }
    @Override
    public StringValue defaultValue() {return new StringValue("");}
    @Override
    public Type deepCopy() {
        return new StringType();
    }
}