package model.exceptions;

public class EmptyCollectionException extends MyExc{
    String message;

    public EmptyCollectionException(String msg) {
        super(msg + "is empty error");
        message = msg + "is empty error";}

    @Override
    public String what() {
        return message;
    }
}
