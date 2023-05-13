package model.ADTS;
import java.util.HashMap;

public interface MyIHeap <K,V> {
    void add(K key, V value);
    void update(K key, V value);
    V lookup(K key);
    boolean isDefined(K key);
    String toString();
    void setContent(HashMap<K,V> newContent);
    HashMap<K,V> getContent();
    void remove(K key);
    MyIHeap<K,V> deepCopy();

    int getFree();

    void setFree(int newFree);
}

