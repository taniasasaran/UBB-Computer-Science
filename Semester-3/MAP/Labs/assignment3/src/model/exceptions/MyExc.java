package model.exceptions;

public class MyExc extends Throwable implements Exc{
    String message;

    public MyExc(String msg) {message = msg;}

    @Override
    public String what() {
        return message;
    }
}
