package model.ADTS;

public interface MyIDictionary<T,V>{
    V add(T t, V v);

    V lookup(T id);

    boolean containsKey(T id);

    V remove(T id);

    boolean isDefined(T id);

    void update(T id, V val);

    String toString();

    boolean isFull();

    int getSize();

    boolean isEmpty();
}
