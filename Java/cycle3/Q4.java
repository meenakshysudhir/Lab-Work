/*Write a Java program that read from a file and write to file by handling all file related ex-
ceptions. ** */
import java.io.*;
public class Q5 {
    public static void main(String[] args) {
        String inputFile = "input.txt"; 
        String outputFile = "output.txt";

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {

            String line;
            while ((line = reader.readLine()) != null) {
                writer.write(line);
                writer.newLine(); // Add a newline to separate lines in the output file
            }

            System.out.println("File read and write successful!");

        } catch (IOException e) {
            System.out.println("Error occurred while processing files: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
