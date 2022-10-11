public class Main {
    public static void main(String[] args) {
        int sum = 0;
        double count = 0;
        int value = 0;
        for (String arg : args) {
            value = Integer.parseInt(arg);
            sum += value;
            count += 1;
        }
        if(count == 0)
            System.out.println("No integers were given");
        else
            System.out.println(sum/count);
    }
}
