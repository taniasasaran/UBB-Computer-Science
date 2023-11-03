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
            LexicAnalyzer lexicAnalyzer = new LexicAnalyzer(programLines, tokens);

            String result = lexicAnalyzer.run();
            Helpers.writeToFile(fileOUT, result + "\n\nST\n" + lexicAnalyzer.getSymbolTable() + "\n\nPIF\n" + lexicAnalyzer.getPIF());

        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}