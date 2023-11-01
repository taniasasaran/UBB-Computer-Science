import java.util.ArrayDeque;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumerQueue<T> {
    private final Lock mutex = new ReentrantLock();
    Queue<T> queue = new ArrayDeque<T>();
    private final Condition conditionVariable = mutex.newCondition();
    private boolean isEnd = false;
    public void enqueue(T val) {
        mutex.lock();
        queue.add(val);
        conditionVariable.signal();
        mutex.unlock();
    }

    /* Gets the next element from the queue. If the queue is empty but not closed, this function blocks.
    If the queue is empty and closed, returns null.*/
    public T dequeue() {
        T ret;
        mutex.lock();
        while (true) {
            if (!queue.isEmpty()) {
                ret = queue.remove();
                mutex.unlock();
                return ret;
            }
            if (isEnd) {
                mutex.unlock();
                return null;
            }
            try {
                conditionVariable.await();
            } catch(InterruptedException e) {
                System.err.println("Exception: " + e);
            }
        }
    }

    /* Closes the queue.*/
    public void close() {
        mutex.lock();
        isEnd = true;
        conditionVariable.signalAll();
        mutex.unlock();
    }
};