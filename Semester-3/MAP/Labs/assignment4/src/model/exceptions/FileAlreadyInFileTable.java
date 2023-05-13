package model.exceptions;

import model.values.Value;

public class FileAlreadyInFileTable extends MyExc {
    String message;

    public FileAlreadyInFileTable(Value msg) {
        super("file " + msg.toString() +" was already declared");
        message = "file " + msg.toString() +" was already declared";}

    @Override
    public String what() {
        return message;
    }
}