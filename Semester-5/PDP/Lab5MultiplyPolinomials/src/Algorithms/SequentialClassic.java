package Algorithms;

import Model.Polynomial;

import java.util.ArrayList;
import java.util.List;

public class SequentialClassic {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) {
        List<Integer> coefficients = new ArrayList<>();
        int resultDegree = p1.getDegree() + p2.getDegree();
        for (int i = 0; i <= resultDegree; i++) {
            coefficients.add(0);
        }
        Polynomial result = new Polynomial(coefficients);

        for (int k = 0; k <= resultDegree; k++) {
            int sum = 0;
            for (int i = 0; i <= k; i++) {
                if (i <= p1.getDegree() && (k - i) <= p2.getDegree()) {
                    sum += p1.getCoefficients().get(i) * p2.getCoefficients().get(k - i);
                }
            }
            result.getCoefficients().set(k, sum);
        }

        return result;
    }
}