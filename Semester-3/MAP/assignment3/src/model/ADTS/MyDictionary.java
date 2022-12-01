package model.ADTS;
import java.util.HashMap;

public class MyDictionary<T,V> implements MyIDictionary<T,V>{
    HashMap<T, V> dict;
    int capacity = 500;

    public MyDictionary(){ this.dict = new HashMap<T,V>(capacity); }

    @Override
    public V add(T t, V v){
        return dict.put(t,v);
    }

    @Override
    public V lookup(T id) { return dict.get(id); }

    @Override
    public boolean containsKey(T id) { return dict.containsKey(id); }

    @Override
    public V remove(T id) { return dict.remove(id); }

    @Override
    public boolean isDefined(T id) {
        return dict.get(id) != null;
    }

    @Override
    public boolean isFull() {
        return dict.size()==capacity;
    }

    @Override
    public int getSize() {
        return dict.size();
    }

    @Override
    public boolean isEmpty(){
        return dict.size()==0;
    }

    @Override
    public void update(T id, V val) {  dict.put(id, val);  }

    @Override
    public String toString() { return dict.toString();}

    public void setDict(HashMap<T, V> dict) {
        this.dict = dict;
    }

    public HashMap<T, V> getDict() {
        return dict;
    }
}
