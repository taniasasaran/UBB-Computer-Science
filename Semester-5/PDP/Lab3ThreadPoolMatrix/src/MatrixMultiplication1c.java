import java.util.Random;
import java.util.ArrayList;
import java.util.List;

public class MatrixMultiplication1c {
    private static int MATRIX_SIZE;
    private static int TASK_COUNT;

    public static void main(int[][] matrixA, int[][] matrixB, int[][] resultMatrix, int size, int count) {
        MATRIX_SIZE = size;
        TASK_COUNT = count;

        Thread[] threads = new Thread[TASK_COUNT];
        List<List<Pair<Integer, Integer>>> taskIndices = calculateTaskIndices();
        long startTime = System.currentTimeMillis();

        for (int taskIndex = 0; taskIndex < TASK_COUNT; taskIndex++) {
            List<Pair<Integer, Integer>> indices = taskIndices.get(taskIndex);
            threads[taskIndex] = new Thread(() -> multiplyKth(matrixA, matrixB, resultMatrix, indices));
            threads[taskIndex].start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        long endTime = System.currentTimeMillis();
        System.out.println("Kth | Time: " + (endTime - startTime) + "ms | " + TASK_COUNT + " threads | matrix size " + MATRIX_SIZE);
    }

    private static List<List<Pair<Integer, Integer>>> calculateTaskIndices() {
        List<List<Pair<Integer, Integer>>> taskIndices = new ArrayList<>();
        for (int i = 0; i < TASK_COUNT; i++) {
            taskIndices.add(new ArrayList<>());
        }

        for (int taskIndex = 0; taskIndex < TASK_COUNT; taskIndex++) {
            Pair<Integer, Integer> elementIndex = new Pair<>(0, taskIndex);
            taskIndices.get(taskIndex).add(elementIndex);
            while (true) {
                Pair<Integer, Integer> startIndex = calculateNextIndex(elementIndex);
                if (startIndex.getFirst() >= MATRIX_SIZE)
                    break;
                taskIndices.get(taskIndex).add(startIndex);
                elementIndex = startIndex;
            }
        }
        return taskIndices;
    }

    private static Pair<Integer, Integer> calculateNextIndex(Pair<Integer, Integer> currentIndex) {
        Integer nextRow = currentIndex.getFirst();
        Integer nextColumn = currentIndex.getSecond();
        if (nextColumn + TASK_COUNT < MATRIX_SIZE) {
            nextColumn += TASK_COUNT;
        } else {
            nextRow++;
            nextColumn = (nextColumn + TASK_COUNT) % MATRIX_SIZE;
        }
        return new Pair<>(nextRow, nextColumn);
    }

    private static void multiplyKth(int[][] matrixA, int[][] matrixB, int[][] resultMatrix, List<Pair<Integer, Integer>> indices) {
        for (Pair<Integer, Integer> index: indices) {
            resultMatrix[index.getFirst()][index.getSecond()] = Main.computeCell(matrixA, matrixB, index.getFirst(), index.getSecond());
        }
    }
}