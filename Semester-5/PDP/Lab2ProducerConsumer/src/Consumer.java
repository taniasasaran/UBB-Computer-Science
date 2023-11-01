public class Consumer implements Runnable {
    private final ProducerConsumerQueue<Integer> queue;

    public Consumer(ProducerConsumerQueue<Integer> queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        int sum = 0;
        int i = 0;
        while (true) {
            System.out.println("Consumer: dequeue " + i);
            Integer x = queue.dequeue();
            if (x == null) {
                break;
            }
            sum += x;
            i += 1;
        }
        System.out.println("Sum=" + sum);
    }
}