import java.util.ArrayList;

public class FiniteAutomata {
    private final String filename;
    private ArrayList<String> states;
    private ArrayList<String> alphabet;
    private String initialState;
    private ArrayList<String> finalStates;
    private ArrayList<Transition> transitions;

    public FiniteAutomata(String filename) {
        this.filename = filename;
        this.states = new ArrayList<>();
        this.alphabet = new ArrayList<>();
        this.finalStates = new ArrayList<>();
        this.transitions = new ArrayList<>();
        this.readFromFile();
    }

    private void readFromFile() {
        ArrayList<String> lines = Helpers.readFileToList(this.filename);
        this.states = Helpers.splitString(lines.get(0));
        this.alphabet = Helpers.splitString(lines.get(1));
        this.initialState = lines.get(2);
        this.finalStates = Helpers.splitString(lines.get(3));
        for (int i = 4; i < lines.size(); i++) {
            String[] tokens = lines.get(i).split(" ");
            this.transitions.add(new Transition(tokens[0], tokens[2], tokens[1]));
        }
    }

    public boolean isDeterministic() {
        for (String state : this.states) {
            for (String symbol : this.alphabet) {
                if (this.getTransitionsFromStateAndSymbol(state, symbol).size() > 1) {
                    return false;
                }
            }
        }
        return true;
    }

    private ArrayList<Transition> getTransitionsFromStateAndSymbol(String state, String symbol) {
        ArrayList<Transition> result = new ArrayList<>();
        for (Transition transition : this.transitions) {
            if (transition.getFromState().equals(state) && transition.getSymbol().equals(symbol)) {
                result.add(transition);
            }
        }
        return result;
    }


    private void printElements(ArrayList<String> elements) {
        StringBuilder result = new StringBuilder();
        for (String state : elements) {
            result.append(state);
            if (elements.size() - 1 != elements.indexOf(state)) {
                result.append(", ");
            }
        }
        System.out.println(result);
    }

    private void printStates() {
        this.printElements(this.states);
    }

    private void printAlphabet() {
        this.printElements(this.alphabet);
    }

    private void printFinalStates() {
        this.printElements(this.finalStates);
    }

    private void printTransitions() {
        for (Transition transition : this.transitions) {
            System.out.println(transition);
        }
    }

    private void printInitialState() {
        System.out.println(this.initialState);
    }

    private void printMenu() {
        System.out.println("1. Print states");
        System.out.println("2. Print alphabet");
        System.out.println("3. Print transitions");
        System.out.println("4. Print initial state");
        System.out.println("5. Print final states");
    }

    public void displayThings() {
        while (true) {
            printMenu();
            String input = Helpers.readUserInput("Enter the input: ");
            if (input.isEmpty()) {
                System.out.println("The input is empty.");
                return;
            }
            switch (input) {
                case "1" -> this.printStates();
                case "2" -> this.printAlphabet();
                case "3" -> this.printTransitions();
                case "4" -> this.printInitialState();
                case "5" -> this.printFinalStates();
                default -> System.out.println("Invalid input.");
            }
        }
    }

    public boolean checkAccepted(String sequence) {
        if (!isDeterministic())
            return false;
        String currentState = this.initialState;
        for (int i = 0; i < sequence.length(); i++) {
            String symbol = String.valueOf(sequence.charAt(i));
            ArrayList<Transition> transitions = this.getTransitionsFromStateAndSymbol(currentState, symbol);
            if (transitions.size() == 0) {
                return false;
            }
            currentState = transitions.get(0).getToState();
        }
        return this.finalStates.contains(currentState);
    }
}
