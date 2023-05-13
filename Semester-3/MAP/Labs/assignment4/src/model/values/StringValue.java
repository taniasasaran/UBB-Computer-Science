package model.values;
import model.types.StringType;
import model.types.Type;

public class StringValue implements Value {
    String val;
    public StringValue(String v){val=v;}
    @Override
    public String getVal() {return val;}
    @Override
    public String toString() { return val; }
    @Override
    public Type getType() { return new StringType(); }
    @Override
    public Value deepCopy() { return new StringValue(val); }
    @Override
    public boolean equals(Value another) { return another instanceof StringValue; }
}
