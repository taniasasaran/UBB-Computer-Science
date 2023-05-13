package model.exceptions;

public class FullCollectionExc extends MyExc{
    String message;

    public FullCollectionExc(String msg) {
        super(msg + "is full error");
        message = msg + "is full error";}

    @Override
    public String what() {
        return message;
    }
}
