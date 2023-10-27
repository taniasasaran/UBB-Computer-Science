public class Main {
    public static void main(String[] args) {
        SymbolTable symbolTable = new SymbolTable(4);

        symbolTable.add("A");
        System.out.println(symbolTable.contains("A"));
        Pair position = symbolTable.getPosition("A");
        String element = symbolTable.get(position);
        System.out.println(position);
        System.out.println(element);

        symbolTable.add("CECE");
        System.out.println(symbolTable.contains("CECE"));
        System.out.println(symbolTable.getPosition("CECE"));
        System.out.println(symbolTable.add("CECE"));

        symbolTable.add("IT");
        System.out.println(symbolTable.contains("IT"));
        System.out.println(symbolTable.getPosition("IT"));

        symbolTable.add("_PRIVATE");
        System.out.println(symbolTable.contains("_PRIVATE"));
        System.out.println(symbolTable.getPosition("_PRIVATE"));

        System.out.println(symbolTable.getHashTable());
        System.out.println(symbolTable.getSize());
        System.out.println(symbolTable.getNumberOfElements());
    }
}