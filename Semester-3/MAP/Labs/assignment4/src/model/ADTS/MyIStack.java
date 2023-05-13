package model.ADTS;

import model.exceptions.FullCollectionExc;
import model.exceptions.MyExc;

import java.util.Stack;

public interface MyIStack<T> {
    T pop() throws MyExc;
    void push(T v) throws MyExc;
    boolean isEmpty();

    boolean isFull();

    String toString();
    String printStack();
    void setStack(Stack<T> stack);

    void setSize(int size);

    void setCapacity(int capacity);

    Stack<T> getStack();

    int getSize();

    int getCapacity();
}
