package model.exceptions;

import model.values.Value;

public class FileNotInFileTable extends MyExc {
    String message;

    public FileNotInFileTable(Value msg) {
        super("file " + msg.toString() +" was already declared");
        message = "file " + msg.toString() +" was already declared";}

    @Override
    public String what() {
        return message;
    }
}