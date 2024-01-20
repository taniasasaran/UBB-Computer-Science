import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

class DSMVariable {
    private int value;
    private Set<Integer> subscribers;

    DSMVariable() {
        this.value = 0;
        this.subscribers = new HashSet<>();
    }

    int getValue() {
        return value;
    }

    void setValue(int value) {
        this.value = value;
    }

    Set<Integer> getSubscribers() {
        return subscribers;
    }

    void addSubscriber(int nodeId) {
        subscribers.add(nodeId);
    }

    void removeSubscriber(int nodeId) {
        subscribers.remove(nodeId);
    }
}

public class DSMLibrary {
    private static Map<Integer, DSMVariable> variables = new HashMap<>();

    public static void createVariable(int variableId) {
        variables.put(variableId, new DSMVariable());
    }

    public static int read(int variableId, int nodeId) {
        DSMVariable variable = variables.get(variableId);
        if (variable != null && variable.getSubscribers().contains(nodeId)) {
            return variable.getValue();
        }
        return -1;
    }

    public static void write(int variableId, int value, int nodeId) {
        DSMVariable variable = variables.get(variableId);
        if (variable != null && variable.getSubscribers().contains(nodeId)) {
            variable.setValue(value);
            notifySubscribers(variableId);
        }
    }

    public static boolean compareAndExchange(int variableId, int expectedValue, int newValue, int nodeId) {
        DSMVariable variable = variables.get(variableId);
        if (variable != null && variable.getSubscribers().contains(nodeId)) {
            synchronized (variable) {
                if (variable.getValue() == expectedValue) {
                    variable.setValue(newValue);
                    notifySubscribers(variableId);
                    return true; // Successful exchange
                } else {
                    return false;
                }
            }
        }
        return false;
    }

    public static void subscribe(int variableId, int nodeId) {
        DSMVariable variable = variables.get(variableId);
        if (variable != null) {
            variable.addSubscriber(nodeId);
        }
    }

    public static void unsubscribe(int variableId, int nodeId) {
        DSMVariable variable = variables.get(variableId);
        if (variable != null) {
            variable.removeSubscriber(nodeId);
        }
    }

    private static void notifySubscribers(int variableId) {
        DSMVariable variable = variables.get(variableId);
        if (variable != null) {
            for (int subscriberId : variable.getSubscribers()) {
                System.out.println("Node " + subscriberId + ": Variable " + variableId + " has changed to " + variable.getValue());
            }
        }
    }
}
