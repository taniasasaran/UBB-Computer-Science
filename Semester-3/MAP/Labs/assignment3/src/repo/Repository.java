package repo;

import model.ADTS.MyIList;
import model.ADTS.MyList;
import model.exceptions.MyExc;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.security.Principal;

public class Repository<T> implements IRepository<T> {

    private MyIList<T> entities;
    String filename;

    public Repository(String fn) {
        entities = new MyList<T>();
        filename = fn;
    }

    @Override
    public int getSize() { return entities.getSize(); }

    @Override
    public void add(T entity) throws MyExc{
        entities.add(entity);
    }

    @Override
    public void remove(T entity) throws MyExc { entities.remove(entity); }

    @Override
    public void logPrgStateExec() throws MyExc {
        try{
            PrintWriter logFile= new PrintWriter(new BufferedWriter(new FileWriter(filename, true)));
            for(int i=0; i<getSize(); i++)
                logFile.printf(getAll().get(i).toString()+"\n");
            logFile.close();
        } catch (IOException e) {
            throw new MyExc(e.getMessage());
        }
    }
    public MyIList<T> getEntities() { return entities; }
    public void setEntities(MyIList<T> entities) { this.entities = entities;}
    public String getFilename() { return filename; }
    public void setFilename(String filename) { this.filename = filename; }
    @Override
    public T getCrtPrg() throws MyExc { return entities.get(entities.getSize()-1);}

    @Override
    public MyIList<T> getAll() {
        return entities;
    }
}
