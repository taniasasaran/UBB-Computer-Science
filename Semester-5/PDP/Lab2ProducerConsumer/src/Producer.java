import java.util.ArrayList;

public class Producer implements Runnable {
    private final ProducerConsumerQueue<Integer> queue;
    private final ArrayList<Integer> vector1;
    private final ArrayList<Integer> vector2;

    public Producer(ProducerConsumerQueue<Integer> queue, ArrayList<Integer> vector1, ArrayList<Integer> vector2) {
        this.queue = queue;
        this.vector1 = vector1;
        this.vector2 = vector2;
    }

    @Override
    public void run() {
        for (int i = 0; i < vector1.size(); ++i) {
            System.out.println("Producer: enqueue " + i);
            queue.enqueue(vector1.get(i) * vector2.get(i));
        }
        queue.close();
    }
}