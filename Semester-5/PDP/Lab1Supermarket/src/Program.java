import java.util.ArrayList;
import java.util.List;

public class Program {
    public static void main(String[] args) throws InterruptedException {
        List<ExtendedProduct> products = FileManipulator.getProducts();
        Supermarket supermarket = new Supermarket(products);
        List<Bill> bills = Bill.getRandomBills(products, 40000);
        int threadNumber = 4;
        int iterations = (int) Math.ceil((double)bills.size()/(double) threadNumber);
        List<Thread> threads = new ArrayList<>();
        int checkThreadNumber = threadNumber;
        for (int i = 0; i < threadNumber; ++i) {
            int start = i*iterations;
            int end = Math.min((i+1)*iterations, bills.size());
            threads.add(new Thread(new ProcessBillsThread(bills.subList(start, end), supermarket, i)));
            if (i % 3 == 0) {
                threads.add(new Thread(new CheckEverythingThread(supermarket, checkThreadNumber)));
                ++checkThreadNumber;
            }
        }
        long startTime = System.currentTimeMillis();
        for (Thread thread : threads)
            thread.start();
        for (Thread thread : threads)
            thread.join();
        long endTime = System.currentTimeMillis();
        System.out.println("Runned with " + threadNumber + " threads");
        System.out.println("Time elapsed: " + (endTime - startTime) + "ms");
        new CheckEverythingThread(supermarket, checkThreadNumber).run();
    }
}