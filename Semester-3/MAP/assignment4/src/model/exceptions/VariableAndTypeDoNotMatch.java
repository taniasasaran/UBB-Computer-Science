package model.exceptions;

public class VariableAndTypeDoNotMatch extends MyExc{
    String message;

    public VariableAndTypeDoNotMatch(String msg) {
        super("declared type of variable" + msg + " and type of the assigned expression do not match");
        message = "declared type of variable" + msg + " and type of the assigned expression do not match";}

    @Override
    public String what() {
        return message;
    }
}
