package model.ADTS;

import model.exceptions.EmptyCollectionException;
import model.exceptions.FullCollectionExc;
import model.exceptions.MyExc;
import model.statements.IStmt;

import java.util.Stack;

public class MyStack<T> implements MyIStack<T> {
    Stack<T> stack;
    int size, capacity;

    public MyStack() { stack = new Stack<T>(); size = 0; capacity = 100; }
    @Override
    public boolean isEmpty() { return stack.empty(); }

    @Override
    public T pop() throws MyExc{ if(isEmpty()) throw new EmptyCollectionException("Stack"); size-=1; return stack.pop();}

    @Override
    public void push(T t) throws MyExc {
        if(isFull())
            throw new FullCollectionExc("Stack");
        stack.push(t);
        size+=1;
    }
    @Override
    public boolean isFull(){
        return size == capacity;
    }
    @Override
    public String toString() { return stack.toString(); }
    @Override
    public String printStack(){
        StringBuilder s = new StringBuilder();
        for(int i= stack.size()-1;i>=0;i--){
            s.append(stack.get(i).toString()).append("\n");
        }
        return s.toString();
    }
    @Override
    public void setStack(Stack<T> stack) {
        this.stack = stack;
    }
    @Override
    public void setSize(int size) {
        this.size = size;
    }
    @Override
    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }
    @Override
    public Stack<T> getStack() {
        return stack;
    }
    @Override
    public int getSize() {
        return size;
    }
    @Override
    public int getCapacity() {
        return capacity;
    }
}