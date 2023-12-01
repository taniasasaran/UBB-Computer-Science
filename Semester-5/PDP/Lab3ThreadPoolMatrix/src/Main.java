import java.util.Arrays;
import java.util.Random;

public class Main {
    private static final int MATRIX_SIZE = 100;
    private static final int TASK_COUNT = 1;

    public static void main(String[] args) {
        int[][] matrixA = generateRandomMatrix();
        int[][] matrixB = generateRandomMatrix();
        int[][] resultMatrix = new int[MATRIX_SIZE][MATRIX_SIZE];
        int[][] trueMatrix = getProductSequentially(matrixA, matrixB);

        MatrixMultiplication1a.main(matrixA, matrixB, resultMatrix, MATRIX_SIZE, TASK_COUNT);
        compareMatrices(trueMatrix, resultMatrix);
        MatrixMultiplication1b.main(matrixA, matrixB, resultMatrix, MATRIX_SIZE, TASK_COUNT);
        compareMatrices(trueMatrix, resultMatrix);
        MatrixMultiplication1c.main(matrixA, matrixB, resultMatrix, MATRIX_SIZE, TASK_COUNT);
        compareMatrices(trueMatrix, resultMatrix);
        MatrixMultiplication2a.main(matrixA, matrixB, resultMatrix, MATRIX_SIZE, TASK_COUNT);
        compareMatrices(trueMatrix, resultMatrix);
        MatrixMultiplication2b.main(matrixA, matrixB, resultMatrix, MATRIX_SIZE, TASK_COUNT);
        compareMatrices(trueMatrix, resultMatrix);
        MatrixMultiplication2c.main(matrixA, matrixB, resultMatrix, MATRIX_SIZE, TASK_COUNT);
        compareMatrices(trueMatrix, resultMatrix);

//        System.out.println("\nMatrix A:");
//        printMatrix(matrixA);
//        System.out.println("\nMatrix B:");
//        printMatrix(matrixB);
//        System.out.println("\nResult Matrix:");
//        printMatrix(resultMatrix);
    }

    private static int[][] generateRandomMatrix() {
        int[][] matrix = new int[MATRIX_SIZE][MATRIX_SIZE];
        Random random = new Random();
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                matrix[i][j] = random.nextInt(5);
            }
        }
        return matrix;
    }

    private static void compareMatrices(int[][] trueMatrix, int[][] resultMatrix) {
        if (Arrays.deepEquals(trueMatrix, resultMatrix)) {
//            System.out.println("Matrices are equal.");
            return;
        } else {
            System.out.println("Matrices are not equal.");
        }
    }

    private static void printMatrix(int[][] matrix) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    public static int computeCell(int[][] matrixA, int [][] matrixB, Integer i, Integer j) {
        int ans = 0;
        for (int k = 0; k < MATRIX_SIZE; ++k)
            ans += matrixA[i][k] * matrixB[k][j];
        return ans;
    }

    public static int[][] getProductSequentially(int[][] matrixA, int[][] matrixB) {
        int[][] product = new int[MATRIX_SIZE][MATRIX_SIZE];
        for (int i = 0; i < MATRIX_SIZE; ++i)
            for (int j = 0; j < MATRIX_SIZE; ++j)
                product[i][j] = computeCell(matrixA, matrixB, i, j);
        return product;
    }
}