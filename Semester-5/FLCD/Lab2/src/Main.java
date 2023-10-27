public class Main {
    public static void main(String[] args) {
        SymbolTable symbolTable = new SymbolTable(4);

        symbolTable.add("A");
        System.out.println(symbolTable.containsTerm("A"));
        Pair position = symbolTable.findPositionOfTerm("A");
        String element = symbolTable.findByPos(position);
        System.out.println(position);
        System.out.println(element);

        symbolTable.add("CECE");
        System.out.println(symbolTable.containsTerm("CECE"));
        System.out.println(symbolTable.findPositionOfTerm("CECE"));
        System.out.println(symbolTable.add("CECE"));

        symbolTable.add("IT");
        System.out.println(symbolTable.containsTerm("IT"));
        System.out.println(symbolTable.findPositionOfTerm("IT"));

        symbolTable.add("_PRIVATE");
        System.out.println(symbolTable.containsTerm("_PRIVATE"));
        System.out.println(symbolTable.findPositionOfTerm("_PRIVATE"));

        System.out.println(symbolTable.getHashTable());
        System.out.println(symbolTable.getSize());
        System.out.println(symbolTable.getNumberOfElements());
    }
}