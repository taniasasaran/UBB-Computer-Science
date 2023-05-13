package model.exceptions;

public class VarNotOfTypeError extends MyExc{
    String id,type;
    public VarNotOfTypeError(String id, String type) {
        super(id + " is not of type " +type);
        message = id + " is not of type " +type;}

    @Override
    public String what() {
        return message;
    }
}
