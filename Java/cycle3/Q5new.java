import java.util.StringTokenizer;

public class Q5new {
    public static void main(String[] args) {
        // Example input: "1 2 3 4 5"
        String input = "1 2 3 4 5"; // Replace with your input or get it from user input

        // Use StringTokenizer to tokenize the input
        StringTokenizer tokenizer = new StringTokenizer(input);

        // Variables to store individual integers and the sum
        int sum = 0;

        // Process each token (integer)
        while (tokenizer.hasMoreTokens()) {
            String token = tokenizer.nextToken();
            int number = Integer.parseInt(token);

            // Display each integer
            System.out.println("Integer: " + number);

            // Add the integer to the sum
            sum += number;
        }

        // Display the sum
        System.out.println("Sum of integers: " + sum);
    }
}
