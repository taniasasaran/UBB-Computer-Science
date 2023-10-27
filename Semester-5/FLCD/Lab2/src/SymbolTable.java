public class SymbolTable {
    private Integer size;
    private HashTable hashTable;

    public SymbolTable(Integer size){
        this.size = size;
        this.hashTable = new HashTable(size);
    }

    public String get(Pair pos){
        return hashTable.get(pos);
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

    public Pair getPosition(String elem){
        return hashTable.getPosition(elem);
    }

    public boolean contains(String elem){
        return hashTable.contains(elem);
    }

    public Pair add(String elem){
        return hashTable.add(elem);
    }
}