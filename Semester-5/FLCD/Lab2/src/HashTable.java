import java.util.ArrayList;
public class HashTable {
    private Integer size;
    private ArrayList<ArrayList<String>> table;

    public HashTable(Integer size) {
        this.size = size;
        this.table = new ArrayList<>();
        for (int i = 0; i < size; i++) {
            this.table.add(new ArrayList<>());
        }
    }

    private Integer hash(String key) {
        int sum_chars = 0;
        char[] key_characters = key.toCharArray();
        for (char c : key_characters) {
            sum_chars += c;
        }
        return sum_chars % size;
    }

    public String get(Pair pos) {
        if (this.table.size() <= pos.getFirst() || this.table.get(pos.getFirst()).size() <= pos.getSecond()) {
            throw new IndexOutOfBoundsException("Invalid position");
        }
        return this.table.get(pos.getFirst()).get(pos.getSecond());
    }

    public Integer getSize() {
        return size;
    }

    public Integer getNumberOfElements() {
        int count = 0;
        for (ArrayList<String> elems : this.table) {
            count += elems.size();
        }
        return count;
    }

    public Pair getPosition(String elem) {
        int pos = hash(elem);
        if (!table.get(pos).isEmpty()) {
            ArrayList<String> elems = this.table.get(pos);
            for (int i = 0; i < elems.size(); i++) {
                if (elems.get(i).equals(elem)) {
                    return new Pair(pos, i);
                }
            }
        }
        return null;
    }

    public boolean contains(String elem) {
        return this.getPosition(elem) != null;
    }

    public Pair add(String elem) {
        Integer pos = hash(elem);
        ArrayList<String> elems = this.table.get(pos);
        for (int i = 0; i < elems.size(); i++) {
            if (elems.get(i).equals(elem)) {
                return new Pair(pos, i);
            }
        }
        elems.add(elem);
        return new Pair(pos, elems.size() - 1);
    }

    @Override
    public String toString() {
        return "SymbolTable { " + "elements=" + table + ", size = " + size + " }";
    }
}