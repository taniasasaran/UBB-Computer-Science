import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        String fileIN, fileOUT;
        fileIN = "resources/p1.in";
        fileOUT = "output/p1.out";
        fileIN = "resources/p2.in";
        fileOUT = "output/p2.out";
        fileIN = "resources/p3.in";
        fileOUT = "output/p3.out";
        fileIN = "resources/p1err.in";
        fileOUT = "output/p1err.out";

        try{
            ArrayList<String> tokens = Helpers.readFileToList("resources/tokens.in");
            ArrayList<String> programLines = Helpers.readFileToList(fileIN);
            FiniteAutomata integersFA = new FiniteAutomata("resources/integer.in");
            FiniteAutomata identifiersFA = new FiniteAutomata("resources/identifier.in");

            LexicAnalyzer lexicAnalyzer = new LexicAnalyzer(programLines, tokens, integersFA, identifiersFA);

            String result = lexicAnalyzer.run();
            Helpers.writeToFile(fileOUT, result + "\n\nST\n" + lexicAnalyzer.getSymbolTable() + "\n\nPIF\n" + lexicAnalyzer.getPIF());

            FiniteAutomata finiteAutomata = new FiniteAutomata("resources/fa.in");
            assert finiteAutomata.isDeterministic();
            finiteAutomata.displayThings();
//            assert !finiteAutomata.checkAccepted("0");
//            assert finiteAutomata.checkAccepted("01");
//            assert finiteAutomata.checkAccepted("1");
//            assert !finiteAutomata.checkAccepted("");


        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}