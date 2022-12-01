package model.ADTS;

import java.util.HashMap;

public interface MyIDictionary<T,V>{
    V add(T t, V v);

    V lookup(T id);

    boolean containsKey(T id);

    V remove(T id);

    boolean isDefined(T id);

    void update(T id, V val);

    String toString();
    String printDict();
    String printKeys();
    boolean isFull();
    int getSize();
    boolean isEmpty();
    MyIDictionary<T,V> deepCopy();
    HashMap<T,V> getDict();
}
