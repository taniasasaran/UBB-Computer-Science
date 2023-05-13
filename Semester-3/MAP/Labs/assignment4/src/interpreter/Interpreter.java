package interpreter;

import controller.Controller;
import model.ADTS.MyDictionary;
import model.ADTS.MyHeap;
import model.ADTS.MyList;
import model.ADTS.MyStack;
import model.PrgState;
import model.exceptions.MyExc;
import model.expressions.ArithExp;
import model.expressions.RelationalExp;
import model.types.BoolType;
import model.types.StringType;
import model.values.BoolValue;
import model.values.StringValue;
import model.values.Value;
import repo.IRepository;
import repo.Repository;
import model.expressions.ValueExp;
import model.expressions.VarExp;
import model.statements.*;
import model.types.IntType;
import model.values.IntValue;
import model.types.RefType;
import model.expressions.ReadHeapExp;
import model.statements.NewStmt;
import view.ExitCommand;
import view.RunExample;
import view.TextMenu;

import java.io.BufferedReader;

public class Interpreter {
    public static void main(String[] args) {
        try {
            CompStmt e0 = new CompStmt(new VarDeclStmt("varf", new StringType()),
                    new CompStmt(new AssignStmt("varf",new ValueExp(new StringValue("test.in"))),
                        new CompStmt(new OpenRFile(new VarExp("varf")),
                                new CompStmt(new VarDeclStmt("varc", new IntType()),
                                    new CompStmt(new ReadFile("varc", new VarExp("varf")),
                                            new CompStmt(new PrintStmt(new VarExp("varc")),
                                                    new CompStmt(new ReadFile("varc", new VarExp("varf")),
                                                        new CompStmt(new PrintStmt(new VarExp("varc")),new CloseRFile(new VarExp("varf"))))))))));
            PrgState prg0 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),e0);
            IRepository repo0 = new Repository(prg0, "log.txt");
            Controller ctr0 = new Controller(repo0);
//            ctr0.add(e0);


            CompStmt ex1 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))), new PrintStmt(new VarExp("v"))));

            PrgState prg1 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex1);
            IRepository repo1 = new Repository(prg1,"log1.txt");
            Controller ctr1 = new Controller(repo1);
//            ctr1.add(ex1);
                
            IStmt ex2 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new VarDeclStmt("b", new IntType()),
                            new CompStmt(new AssignStmt("a", new ArithExp(1, new ValueExp(new IntValue(2)), new ArithExp(3, new ValueExp(new IntValue(3)), new ValueExp(new IntValue(5))))),
                                    new CompStmt(new AssignStmt("b", new ArithExp(1, new VarExp("a"), new ValueExp(new IntValue(1)))), new PrintStmt(new VarExp("b"))))));

            PrgState prg2 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex2);
            IRepository repo2 = new Repository(prg2, "log2.txt");
            Controller ctr2 = new Controller(repo2);
//            ctr2.add(ex2);

            IStmt ex3 = new CompStmt(new VarDeclStmt("a", new BoolType()),
                    new CompStmt(new VarDeclStmt("v", new IntType()),
                            new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                    new CompStmt(new IfStmt(new VarExp("a"), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                            VarExp("v"))))));
            PrgState prg3 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex3);
            IRepository repo3 = new Repository(prg3, "log3.txt");
            Controller ctr3 = new Controller(repo3);
//            ctr3.add(ex3);

            IStmt ex4 = new CompStmt(new VarDeclStmt("a", new IntType()),
                    new CompStmt(new VarDeclStmt("v", new IntType()),
                            new CompStmt(new AssignStmt("a", new ValueExp(new IntValue(4))),
                                    new CompStmt(new IfStmt(new RelationalExp(new ValueExp(new IntValue(5)),new VarExp("a"),2), new AssignStmt("v", new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))), new PrintStmt(new
                                            VarExp("v"))))));
            PrgState prg4 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex4);
            IRepository repo4 = new Repository(prg4, "log4.txt");
            Controller ctr4 = new Controller(repo4);
//            ctr4.add(ex4);

            IStmt ex5 = new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                            new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), 5),
                                    new CompStmt(new PrintStmt(new VarExp("v")),
                                            new AssignStmt("v", new ArithExp(2, new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                    new PrintStmt(new VarExp("v")))));
            PrgState prg5 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex5);
            IRepository repo5 = new Repository(prg5, "log5.txt");
            Controller ctr5 = new Controller(repo5);
//            ctr5.add(ex5);

//            Ref int v;new(v,20);Ref Ref int a; new(a,v);print(v);print(a)
            IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new PrintStmt(new VarExp("v")),
                                                    new PrintStmt(new VarExp("a")))))));
            PrgState prg6 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex6);
            IRepository repo6 = new Repository(prg6, "log6.txt");
            Controller ctr6 = new Controller(repo6);

//            Ref int v;new(v,20);print(rH(v)); wH(v,30);print(rH(v)+5);
            IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                    new CompStmt(new WriteHeapStmt("v", new ValueExp(new IntValue(30))),
                                            new PrintStmt(new ArithExp(1, new ReadHeapExp(new VarExp("v")), new ValueExp(new IntValue(5))))))));
            PrgState prg7 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex7);
            IRepository repo7 = new Repository(prg7, "log7.txt");
            Controller ctr7 = new Controller(repo7);

//            Ref int v;new(v,20);Ref Ref int a; new(a,v);print(rH(v));print(rH(rH(a))+5)
            IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                    new PrintStmt(new ArithExp(1, new ReadHeapExp(new ReadHeapExp(new VarExp("a"))), new ValueExp(new IntValue(5)))))))));
            PrgState prg8 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex8);
            IRepository repo8 = new Repository(prg8, "log8.txt");
            Controller ctr8 = new Controller(repo8);

//            Ref int v;new(v,20);Ref Ref int a; new(a,v); new(v,30);print(rH(rH(a)))
            IStmt ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                    new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                            new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                    new CompStmt(new NewStmt("a", new VarExp("v")),
                                            new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                    new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a")))))))));
            PrgState prg9 = new PrgState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), new MyDictionary<Value, BufferedReader>(),new MyHeap<Integer, Value>(),ex9);
            IRepository repo9 = new Repository(prg9, "log9.txt");
            Controller ctr9 = new Controller(repo9);

            TextMenu menu = new TextMenu();
            menu.addCommand(new ExitCommand("0", "exit"));
            menu.addCommand(new RunExample("1", ex1.toString(), ctr1));
            menu.addCommand(new RunExample("2", ex2.toString(), ctr2));
            menu.addCommand(new RunExample("3", ex3.toString(), ctr3));
            menu.addCommand(new RunExample("4", ex4.toString(), ctr4));
            menu.addCommand(new RunExample("5", ex5.toString(), ctr5));
            menu.addCommand(new RunExample("6", ex6.toString(), ctr6));
            menu.addCommand(new RunExample("7", ex7.toString(), ctr7));
            menu.addCommand(new RunExample("8", ex8.toString(), ctr8));
            menu.addCommand(new RunExample("9", ex9.toString(), ctr9));
            menu.addCommand(new RunExample("10", e0.toString(), ctr0));
            menu.show();
        }
        catch (MyExc e){
            System.out.println(e.what());
        }
    }
}