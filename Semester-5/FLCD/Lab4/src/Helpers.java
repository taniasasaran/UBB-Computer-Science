import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

public class Helpers {
    public static ArrayList<String> readFileToList(String filename) {
        ArrayList<String> lines = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                lines.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return lines;
    }

    public static void writeToFile(String filename, String content) {
        try {
            java.io.FileWriter myWriter = new java.io.FileWriter(filename);
            myWriter.write(content);
            myWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static ArrayList<String> splitString(String s) {
        String[] tokens = s.split(" ");
        return new ArrayList<>(Arrays.asList(tokens));
    }

    public static String readUserInput(String message) {
        System.out.println(message);
        java.util.Scanner scanner = new java.util.Scanner(System.in);
        return scanner.nextLine();
    }
}
