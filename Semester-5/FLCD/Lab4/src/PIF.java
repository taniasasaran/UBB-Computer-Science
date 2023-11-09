import java.util.ArrayList;

public class PIF {
    private ArrayList<PIFEntry> elems;

    public PIF() {
        this.elems = new ArrayList<>();
    }

    public void add(String token, Pair position) {
        this.elems.add(new PIFEntry(token, position));
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();
        for (PIFEntry elem : this.elems) {
            result.append(elem.toString()).append("\n");
        }
        return result.toString();
    }
}
