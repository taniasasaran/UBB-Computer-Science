import java.util.ArrayList;
import java.util.Arrays;

public class LexicAnalyzer {
    private SymbolTable symbolTable;
    private PIF pif;
    private ArrayList<String> program;
    private ArrayList<String> tokens;

    public LexicAnalyzer(ArrayList<String> program, ArrayList<String> tokens) {
        this.symbolTable = new SymbolTable(5);
        this.pif = new PIF();
        this.program = program;
        this.tokens = tokens;
    }

    public SymbolTable getSymbolTable() {
        return this.symbolTable;
    }

    public PIF getPIF() {
        return this.pif;
    }

    private ArrayList<ArrayList<String>> detect() {
        ArrayList<ArrayList<String>> lines = new ArrayList<>();
        for (String line : program) {
            String[] tokens = line.split(" ");
            ArrayList<String> tokensList;
            tokensList = new ArrayList<>(Arrays.asList(tokens));
            if (tokensList.contains("$")) {
                int index = tokensList.indexOf("$");
                tokensList = new ArrayList<>(tokensList.subList(0, index + 1));
            }
            ArrayList<String> finalTokensList = new ArrayList<>();
            for (String token : tokensList) {
                if (token.matches("^.*[',]$")) {
                    String newToken = token.substring(0, token.length() - 1);
                    if (newToken.length() > 0)
                        finalTokensList.add(newToken);
                    finalTokensList.add(token.substring(token.length() - 1));
                } else
                    finalTokensList.add(token);
            }
            lines.add(finalTokensList);
        }
        return lines;
    }

    private boolean isToken(String token) {
        for (String t : tokens) {
            if (t.equals(token)) {
                return true;
            }
        }
        return false;
    }

    private boolean isIdentifier(String token) {
        return token.matches("^[A-Z_][A-Z_0-9]*$");
    }

    private boolean isConstant(String token) {
        if (token.matches("^0|-?[1-9][0-9]*$")) {
            return true;
        }
        if (token.matches("^\"[a-zA-Z0-9_]*\"$")) {
            return true;
        }
        if (token.matches("^true|false$")) {
            return true;
        }
        return false;
    }

    public String run() {
        ArrayList<ArrayList<String>> toks = detect();
        for (int i = 0; i < toks.size(); i++) {
            for (int j = 0; j<toks.get(i).size(); j++) {
                String token = toks.get(i).get(j);
                if (isToken(token)) {
                    pif.add("\"" + token + "\"", new Pair(-1, -1));
                } else if (isIdentifier(token)) {
                    Pair position = symbolTable.add(token);
                    pif.add("id", position);
                } else if (isConstant(token)) {
                    Pair position = symbolTable.add(token);
                    pif.add("const", position);
                } else {
                    return ("Lexical error on line " + ( i + 1 ) + " token number " + ( j + 1 )
                            + ": " + token + " is not a valid token");
                }
            }
        }
        return "Program is lexically correct.";
    }
}
