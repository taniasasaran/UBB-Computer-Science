package view;

import controller.Controller;
import model.exceptions.MyExc;
import model.exceptions.MyException;

public class RunExample extends Command {
    private Controller ctr;
    public RunExample(String key, String desc,Controller ctr){
        super(key, desc);
        this.ctr=ctr;
    }
    @Override
    public void execute() {
        try{
            ctr.allStep(true); }
        catch (MyExc e) {
            System.out.println(e.what());
        }
    }
}