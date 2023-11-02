import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        ArrayList<String> tokens = Helpers.readFileToList("src/tokens.in");
        ArrayList<String> programLines = Helpers.readFileToList("src/p1.in");
//        ArrayList<String> programLines = Helpers.readFileToList("src/p2.in");
//        ArrayList<String> programLines = Helpers.readFileToList("src/p3.in");
//        ArrayList<String> programLines = Helpers.readFileToList("src/p1err.in");
        LexicAnalyzer lexicAnalyzer = new LexicAnalyzer(programLines, tokens);
        try{
            lexicAnalyzer.run();

            System.out.println(lexicAnalyzer.getPIF());
            System.out.println(lexicAnalyzer.getSymbolTable());

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}