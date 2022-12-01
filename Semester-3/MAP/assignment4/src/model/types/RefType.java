package model.types;

import model.values.RefValue;

import java.util.Objects;

public class RefType implements Type {
    Type inner;
    public RefType(Type inner) {this.inner=inner;}
    public Type getInner() {
//        if(Objects.equals(inner.toString(), "RefType"))
//            return ((RefType)inner).getInner();
        return inner;
    }
    @Override
    public boolean equals(Object another){
        if (another instanceof RefType)
            return inner.equals(((RefType) another).getInner());
        else
            return false;
    }
    @Override
    public String toString() { return "Ref " +inner.toString();}
    @Override
    public Type deepCopy() { return new RefType(inner);}
    @Override
    public RefValue defaultValue() { return new RefValue(0,inner);}
}