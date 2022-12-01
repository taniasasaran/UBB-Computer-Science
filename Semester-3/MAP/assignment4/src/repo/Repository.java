package repo;

import model.ADTS.MyIList;
import model.ADTS.MyList;
import model.PrgState;
import model.exceptions.MyExc;
import model.statements.IStmt;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Repository implements IRepository {

    private MyIList<PrgState> entities;
    String filename;
    PrgState start;
    public Repository(PrgState st, String fn) throws MyExc {
        entities = new MyList<PrgState>();
        entities.add(st);
        filename = fn;
        start = st;
        try{
            PrintWriter logFile= new PrintWriter(new BufferedWriter(new FileWriter(filename, false)));
            logFile.close();
        } catch (IOException e) {
            throw new MyExc(e.getMessage());
        }
    }

    @Override
    public int getSize() { return entities.getSize(); }

    @Override
    public void add(PrgState entity) throws MyExc{
        entities.add(entity);
    }

    @Override
    public void remove(PrgState entity) throws MyExc { entities.remove(entity); }

    @Override
    public void logPrgStateExec() throws MyExc {
        try{
            PrintWriter logFile= new PrintWriter(new BufferedWriter(new FileWriter(filename, true)));
            for(int i=0; i<getSize(); i++)
                logFile.println(getAll().get(i).toString());
            logFile.close();
        } catch (IOException e) {
            throw new MyExc(e.getMessage());
        }
    }
    public MyIList<PrgState> getEntities() { return entities; }
    public void setEntities(MyIList<PrgState> entities) { this.entities = entities;}
    public String getFilename() { return filename; }
    public void setFilename(String filename) { this.filename = filename; }
    public PrgState getStart() { return start; }
    public void setStart(PrgState start) { this.start = start; }
    @Override
    public PrgState getCrtPrg() throws MyExc { return entities.get(entities.getSize()-1);}

    @Override
    public MyIList<PrgState> getAll() {
        return entities;
    }
}
