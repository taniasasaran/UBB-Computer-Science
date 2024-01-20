public class Main {
    public static void main(String[] args) {
        int node1 = 1;
        int node2 = 2;
        int node3 = 3;

        DSMLibrary.createVariable(1);
        DSMLibrary.createVariable(2);

        DSMLibrary.subscribe(1, node1);
        DSMLibrary.subscribe(1, node2);
        DSMLibrary.subscribe(2, node2);
        DSMLibrary.subscribe(2, node3);

        DSMLibrary.write(1, 42, node1);
        DSMLibrary.write(2, 100, node2);
        DSMLibrary.write(2, 43, node2);
        DSMLibrary.compareAndExchange(2, 43, 101, node3);
        boolean success = DSMLibrary.compareAndExchange(1, 42, 20, node1);
        if (success) {
            System.out.println("CAS operation successful!");
        } else {
            System.out.println("CAS operation failed!");
        }

        int value1 = DSMLibrary.read(1, node1);
        int value2 = DSMLibrary.read(2, node3);

        System.out.println("Value of variable 1 at node 1: " + value1);
        System.out.println("Value of variable 2 at node 3: " + value2);
    }
}
