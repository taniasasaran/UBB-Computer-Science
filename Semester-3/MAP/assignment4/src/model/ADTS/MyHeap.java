package model.ADTS;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;

public class MyHeap <K,V> implements MyIHeap<K,V> {
    private HashMap<K,V> content;
    private int free;
    private Stack<K> freePos;

    public MyHeap(){
        content = new HashMap<>();
        free = 1;
        freePos = new Stack<>();
    }

    @Override
    public void add(K key, V value) {
        content.put(key,value);
    }

    @Override
    public void update(K key, V value) {
        content.put(key,value);
    }

    @Override
    public V lookup(K key) {
        return content.get(key);
    }

    @Override
    public boolean isDefined(K key) {
        return content.get(key) != null;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for(K key:content.keySet()){
            s.append(key.toString()).append("->").append(content.get(key).toString()).append("\n");
        }
        return s.toString();
    }

    @Override
    public void setContent(HashMap<K, V> newContent) {
        content = newContent;
    }

    @Override
    public HashMap<K, V> getContent() {
        return content;
    }

    @Override
    public void remove(K key) {
        content.remove(key); freePos.add(key);
    }

    @Override
    public MyIHeap<K, V> deepCopy() {
        MyIHeap<K,V> newHeap = new MyHeap<>();
        for(K key:content.keySet())
            newHeap.add(key,content.get(key));
        return newHeap;
    }

    @Override
    public int getFree() {
        while(true) {
            if (!freePos.isEmpty())
                return (Integer) freePos.pop();
            if (!content.containsKey(free))
                return free;
            else
                free += 1;
        }
    }

    @Override
    public void setFree(int newFree) {
        free = newFree;
    }
}
