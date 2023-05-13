package view;

import controller.Controller;
import model.exceptions.MyExc;
import model.expressions.ArithExp;
import model.expressions.ValueExp;
import model.expressions.VarExp;
import model.statements.*;
import model.types.BoolType;
import model.types.IntType;
import model.values.BoolValue;
import model.values.IntValue;
import java.util.Scanner;


public class View {

    Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    void printMenu(){
        System.out.println("What do you want to run? Type 1 for ex1, 2 for ex2 or 3 for ex3. 0 to exit.");
    }

    public void execute() {
        // 1< 2<= 3== 4>= 5> 6!=
        //1-plus, 2-minus, 3-star, 4-divide
        printMenu();
        Scanner in = new Scanner(System.in);
        int user_command;
        boolean display_flag;
        while(true) {
            user_command = in.nextInt();
            if (user_command == 1) {
                display_flag = in.nextBoolean();
                user_command = in.nextInt();
                IStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));
                if(user_command==4) ex1 = new CompStmt(new VarDeclStmt("v", new IntType()), new PrintStmt(new VarExp("v")));
                if(user_command==5) ex1 = new PrintStmt(new VarExp("v"));
                try {
//                    controller.add(ex1);
                    controller.allStep(display_flag);
                } catch (MyExc e) {
                    System.out.println("ERROR: " + e.what());
                }
            } else if (user_command == 2) {
                display_flag = in.nextBoolean();
                IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                        new CompStmt(new VarDeclStmt("b", new IntType()),
                                new CompStmt(new AssignStmt("a", new ArithExp(1, new ValueExp(new IntValue(2)), new ArithExp(3, new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                        new CompStmt(new AssignStmt("b", new ArithExp(1, new VarExp("a"), new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));
                try {
//                    controller.add(ex2);
                    controller.allStep(display_flag);
                } catch (MyExc e) {
                    System.out.println("ERROR: " + e.what());
                }
            } else if (user_command == 3) {
                display_flag = in.nextBoolean();
                IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                        new CompStmt(new VarDeclStmt("v", new IntType()),
                                new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                        new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                                VarExp("v"))))));
                try {
//                    controller.add(ex3);
                    controller.allStep(display_flag);
                } catch (MyExc e) {
                    System.out.println("ERROR: " + e.what());
                }
            } else if (user_command == 0)
                break;
            else {
                System.out.println("I don't have that many examples sowwy :(");
            }
        }
    }
}


