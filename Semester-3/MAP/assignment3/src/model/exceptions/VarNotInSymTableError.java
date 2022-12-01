package model.exceptions;

public class VarNotInSymTableError extends MyExc{
    String message;

    public VarNotInSymTableError(String msg) {
        super("variable " + msg +" was not declared in this scope");
        message = "variable " + msg +" was not declared in this scope";}

    @Override
    public String what() {
        return message;
    }
}
