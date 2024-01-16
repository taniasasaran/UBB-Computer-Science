import java.util.Collections;
import java.util.List;
import java.util.Vector;

public class Main {

    public static void main(String[] args) {
        int[][] adjacencyMatrix = {
                {0, 1, 1, 1, 1, 0, 0, 1},
                {1, 0, 1, 1, 0, 1, 0, 0},
                {1, 1, 0, 1, 1, 0, 1, 1},
                {1, 1, 1, 0, 0, 0, 1, 1},
                {1, 0, 1, 0, 0, 1, 0, 1},
                {0, 1, 0, 0, 1, 0, 1, 1},
                {0, 0, 1, 1, 0, 1, 0, 1},
                {1, 0, 1, 1, 1, 1, 1, 0}
        };
//        int[][] adjacencyMatrix = {
//                {0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
//                {1, 0, 1, 1, 1, 1, 0, 0, 1, 0},
//                {1, 1, 0, 1, 1, 1, 0, 0, 0, 1},
//                {1, 1, 1, 0, 1, 1, 0, 1, 0, 0},
//                {1, 1, 1, 1, 0, 0, 1, 0, 0, 1},
//                {1, 1, 1, 1, 0, 0, 1, 0, 1, 0},
//                {1, 0, 0, 0, 1, 1, 0, 1, 1, 0},
//                {1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
//                {0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
//                {0, 0, 1, 0, 1, 0, 0, 1, 1, 0}
//        };

//        Graph graph = new Graph(adjacencyMatrix);

        Graph graph = new Graph(100);
//        Vector<Integer> codes = List.of(0, 1, 2, 3, 4, 5, 6, 7).stream().collect(Vector::new, Vector::add, Vector::addAll);
        Vector<Integer> codes = new Vector<>();
        for (int i = 0; i < 100; i++) {
            codes.add(i);
        }
//        Vector<String> colors = List.of("red", "green", "blue", "yellow", "orange", "purple", "pink", "brown").stream().collect(Vector::new, Vector::add, Vector::addAll);

        int threadsNo = 4;
        Vector<Integer> result = new Vector<>();
        long startTime = System.currentTimeMillis();
        try {
            result = GraphColoring.getGraphColoring(threadsNo, graph, codes);
        } catch (GraphColoringException e) {
            System.out.println(e);
        }
        long endTime = System.currentTimeMillis();

        Vector<String> resultColors = new Vector<>();
//        for (int i = 0; i < result.size(); i++) {
//            resultColors.add(colors.get(result.get(i)));
//        }
        System.out.println(result);
        System.out.println(resultColors);
        System.out.println("Number of colors: " + (1 + Collections.max(result)));
        System.out.println("Graph vertices: " + graph.getNodesNo());
        System.out.println("Number of threads: " + threadsNo);
        System.out.println("Total execution time: " + (endTime - startTime) + "ms\n");
    }
}