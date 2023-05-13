package model.exceptions;

public class ExeStackIsEmpty extends MyExc{
    String message;
    public ExeStackIsEmpty() {
        super("cannot execute next statement because the execution stack is empty\nend of program");
        message = "cannot execute next statement because the execution stack is empty\nend of program";
}

    @Override
    public String what() {
        return message;
    }
}