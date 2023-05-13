package model.values;

import model.types.Type;

public interface Value {
    Type getType();
    Object getVal();
    String toString();
    Value deepCopy();
    boolean equals(Value another);
}
