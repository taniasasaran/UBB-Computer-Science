package model.exceptions;

public class DivisionByZeroException extends MyExc{
    String message;

    public DivisionByZeroException() {
        super("division by zero error");
        message = "division by zero error";}

    @Override
    public String what() {
        return message;
    }
}
