package model.types;

import model.statements.CompStmt;
import model.statements.IStmt;
import model.values.Value;

public interface Type {
    Type deepCopy();
    boolean equals(Object another);
    String toString();
    Value defaultValue();
}
