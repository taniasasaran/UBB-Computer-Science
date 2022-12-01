package model.exceptions;

import model.values.Value;

public class VarAlreadyInSymTable extends MyExc{
    String message;

    public VarAlreadyInSymTable(String msg) {
        super("variable " + msg +" was already declared");
        message = "variable " + msg +" was already declared";}

    @Override
    public String what() {
        return message;
    }
}