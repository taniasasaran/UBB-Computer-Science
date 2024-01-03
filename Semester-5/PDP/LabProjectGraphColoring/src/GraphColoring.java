import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class GraphColoring {
//    private static final int NUM_VERTICES = 4;
//    private static final int[][] ADJACENCY_MATRIX = {
//            {0, 1, 1, 1},
//            {1, 0, 1, 0},
//            {1, 1, 0, 1},
//            {1, 0, 1, 0}
//    };
    private static final int NUM_VERTICES = 8;
//    private static final int[][] ADJACENCY_MATRIX = {
//            {0, 1, 1, 1, 0, 0, 0, 0},
//            {1, 0, 1, 0, 1, 0, 0, 0},
//            {1, 1, 0, 0, 0, 1, 0, 0},
//            {1, 0, 0, 0, 1, 0, 1, 0},
//            {0, 1, 0, 1, 0, 0, 0, 1},
//            {0, 0, 1, 0, 0, 0, 1, 0},
//            {0, 0, 0, 1, 0, 1, 0, 1},
//            {0, 0, 0, 0, 1, 0, 1, 0}
//    };
    private static final int[][] ADJACENCY_MATRIX = {
            {0, 1, 1, 1, 1, 0, 0, 0},
            {1, 0, 1, 1, 0, 1, 0, 0},
            {1, 1, 0, 1, 1, 0, 1, 1},
            {1, 1, 1, 0, 0, 0, 1, 1},
            {1, 0, 1, 0, 0, 1, 0, 1},
            {0, 1, 0, 1, 1, 0, 1, 1},
            {0, 0, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 1, 1, 0}
    };
    private static final int MAX_NUM_COLORS = NUM_VERTICES;

    private static List<Thread> threadList = new ArrayList<>();

    public static void main(String[] args) {
        ExecutorService executorService = Executors.newFixedThreadPool(NUM_VERTICES);

        for (int i = 0; i < NUM_VERTICES; i++) {
            Runnable task = new ColoringTask(i);
            Thread thread = new Thread(task);
            threadList.add(thread);
            executorService.execute(thread);
        }

        try {
            executorService.shutdown();
            executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        for (Thread thread : threadList) {
            thread.interrupt();
        }

        System.out.println("Coloring result: " + ColoringTask.bestColoring);
        System.out.println("Number of colors: " + ColoringTask.numColors);
    }

    static class ColoringTask implements Runnable {
        private int vertex;
        static volatile List<Integer> bestColoring = new ArrayList<>();
        static int numColors;

        ColoringTask(int vertex) {
            this.vertex = vertex;
        }

        @Override
        public void run() {
            List<Integer> currentColoring = new ArrayList<>();
            exploreColoring(vertex, currentColoring);
        }

        private void exploreColoring(int vertex, List<Integer> currentColoring) {
            if (Thread.interrupted()) {
                return;
            }

            for (int color = 1; color <= MAX_NUM_COLORS; color++) {
                if (vertex == 3) {
                    System.out.println("Thread " + Thread.currentThread().getId() + " exploring coloring " + currentColoring);
                }
                if (isSafe(vertex, currentColoring, color)) {
                    currentColoring.add(color);

                    if (vertex == NUM_VERTICES - 1) {
                        // All vertices colored successfully, check if it's the best coloring so far
                        updateBestColoring(currentColoring);
                    } else {
                        // Explore next vertex
                        exploreColoring(vertex + 1, currentColoring);
                    }

                    currentColoring.remove(currentColoring.size() - 1);
                }
            }
        }

        private boolean isSafe(int vertex, List<Integer> currentColoring, int color) {
            for (int i = 0; i < NUM_VERTICES; i++) {
                if (ADJACENCY_MATRIX[vertex][i] == 1 && currentColoring.size() > i && currentColoring.get(i) == color) {
                    return false;
                }
            }
            return true;
        }

        private void updateBestColoring(List<Integer> currentColoring) {
            synchronized (bestColoring) {
                if (bestColoring.isEmpty() || currentColoring.size() > bestColoring.size()) {
                    bestColoring.clear();
                    bestColoring.addAll(currentColoring);
                    numColors = bestColoring.stream().max(Integer::compareTo).get();
                }
            }
        }
    }
}
