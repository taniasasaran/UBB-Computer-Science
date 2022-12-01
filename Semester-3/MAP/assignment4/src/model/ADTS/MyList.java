package model.ADTS;

import model.exceptions.EmptyCollectionException;
import model.exceptions.FullCollectionExc;
import model.exceptions.MyExc;

import java.util.Vector;

public class MyList<T> implements MyIList<T>{
    Vector<T> list;
    int capacity = 100;

    public MyList() { this.list = new Vector<T>(capacity); }

    @Override
    public void remove(int i) { list.remove(i); }

    @Override
    public void remove(T elem) throws MyExc { if(isEmpty()) throw new EmptyCollectionException("List"); list.remove(elem); }

    @Override
    public void removeLast() throws MyExc { if(isEmpty()) throw new EmptyCollectionException("List"); list.remove(list.size()-1); }

    @Override
    public boolean isFull(){
        return list.size() == list.capacity();
    }
    @Override
    public boolean isEmpty(){
        return list.isEmpty();
    }
    @Override
    public int getSize() { return list.size(); }

    @Override
    public void update(int pos, T v) throws MyExc { if(pos<0 || pos>getSize()) throw new MyExc("index out of range"); list.setElementAt(v,pos); }

    @Override
    public T get(int pos)  throws MyExc { if(pos<0 || pos>getSize()) throw new MyExc("index out of range"); return list.get(pos); }

    @Override
    public void add(T v) throws MyExc{
        if(isFull()) throw new FullCollectionExc("List"); list.add(v);
    }

    @Override
    public String toString() {
        String s = "";
        for(T element:list)
            s = s + " " + element.toString();
        return s;
    }
//        return list.toString(); }
    @Override
    public String printList(){
        StringBuilder s = new StringBuilder();
        for(T element:list)
            s.append(element.toString()).append("\n");
        return s.toString();
    }

    @Override
    public Vector<T> getList() {
        return list;
    }
    @Override
    public void setList(Vector<T> list) {
        this.list = list;
    }
}
