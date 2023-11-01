import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class FileManipulator {
    public static List<ExtendedProduct> getProducts() {
        Scanner reader;
        try {
            reader = new Scanner(new BufferedInputStream(new FileInputStream("products.txt")));
        } catch (FileNotFoundException e) {
            return new ArrayList<>();
        }
        List<ExtendedProduct> products = new ArrayList<>();
        int n = reader.nextInt();
        for (int i = 0; i < n; ++i) {
            String name = reader.next();
            int quantity = reader.nextInt();
            int price = reader.nextInt();
            products.add(new ExtendedProduct(name, quantity*100, price));
        }
        return products;
    }
}