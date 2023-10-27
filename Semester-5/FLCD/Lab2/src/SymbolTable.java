public class SymbolTable {

    private Integer size;
    private HashTable hashTable;


    public SymbolTable(Integer size){
        hashTable = new HashTable(size);
    }

    public String findByPos(Pair pos){
        return hashTable.findByPos(pos);
    }

    public HashTable getHashTable(){
        return hashTable;
    }

    public Integer getSize(){
        return hashTable.getSize();
    }

    public Integer getNumberOfElements(){
        return hashTable.getNumberOfElements();
    }

    public Pair findPositionOfTerm(String term){
        return hashTable.findPositionOfTerm(term);
    }

    public boolean containsTerm(String term){
        return hashTable.containsTerm(term);
    }

    public boolean add(String term){
        return hashTable.add(term);
    }

}