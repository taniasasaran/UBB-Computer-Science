package model.ADTS;

import model.exceptions.MyExc;

import java.util.Vector;

public interface MyIList<T> {
    void remove(int i);

    T get(int pos) throws MyExc;

    void add(T v) throws MyExc;

    void remove(T elem) throws MyExc;

    void removeLast() throws MyExc;

    boolean isFull();

    boolean isEmpty();

    int getSize();

    void update(int pos, T v) throws MyExc;

    String toString();
    String printList();

    Vector<T> getList();

    void setList(Vector<T> list);
}
