import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class MatrixMultiplication2a {
    private static int MATRIX_SIZE;
    private static int TASK_COUNT;
    private static int ELEMENTS_PER_TASK;
    private static int EXTRA_ELEMENTS;

    public static void main(int[][] matrixA, int[][] matrixB, int[][] resultMatrix, int size, int count) {
        MATRIX_SIZE = size;
        TASK_COUNT = count;
        int TOTAL_ELEMENTS = MATRIX_SIZE * MATRIX_SIZE;
        ELEMENTS_PER_TASK = TOTAL_ELEMENTS / TASK_COUNT;
        EXTRA_ELEMENTS = TOTAL_ELEMENTS % TASK_COUNT;

        ExecutorService executorService = Executors.newFixedThreadPool(TASK_COUNT);
        List<Pair<Pair<Integer, Integer>, Pair<Integer, Integer>>> taskIndices = calculateTaskIndices();
        long startTime = System.currentTimeMillis();

        for (int taskIndex = 0; taskIndex < TASK_COUNT; taskIndex++) {
            Pair<Pair<Integer, Integer>, Pair<Integer, Integer>> indices = taskIndices.get(taskIndex);
            Pair<Integer, Integer> start = indices.getFirst();
            Pair<Integer, Integer> end = indices.getSecond();
            executorService.execute(() -> multiplyRows(matrixA, matrixB, resultMatrix, start, end));
        }

        executorService.shutdown();
        try {
            executorService.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        long endTime = System.currentTimeMillis();
        System.out.println("Row | Time: " + (endTime - startTime) + "ms | " + TASK_COUNT + " tasks with thread pool | matrix size " + MATRIX_SIZE);
    }

    private static List<Pair<Pair<Integer, Integer>, Pair<Integer, Integer>>> calculateTaskIndices() {
        List<Pair<Pair<Integer, Integer>, Pair<Integer, Integer>>> taskIndices = new ArrayList<>();

        int elementIndex = 0;

        for (int taskIndex = 0; taskIndex < TASK_COUNT; taskIndex++) {
            int elementsForTask = ELEMENTS_PER_TASK + (taskIndex < EXTRA_ELEMENTS ? 1 : 0);
            Pair<Integer, Integer> startIndex = calculateIndex(elementIndex);
            elementIndex += elementsForTask;
            Pair<Integer, Integer> endIndex = calculateIndex(elementIndex - 1);
            taskIndices.add(new Pair<>(startIndex, endIndex));
        }

        return taskIndices;
    }

    private static Pair<Integer, Integer> calculateIndex(int elementIndex) {
        int row = elementIndex / MATRIX_SIZE;
        int col = elementIndex % MATRIX_SIZE;
        return new Pair<>(row, col);
    }

    private static void multiplyRows(int[][] matrixA, int[][] matrixB, int[][] resultMatrix, Pair<Integer, Integer> start, Pair<Integer, Integer> end) {
        for (int i = start.getFirst(); i <= end.getFirst(); i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                if (i == start.getFirst() && j < start.getSecond()) {
                    continue;
                }
                if (i == end.getFirst() && j > end.getSecond()) {
                    continue;
                }
                resultMatrix[i][j] = Main.computeCell(matrixA, matrixB, i, j);
            }
        }
    }
}
