import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;

public class Q1 {

    public static void main(String[] args) {
        // Write to a file
        writeToFile("output.txt", "Hello, this is a file handling example!");

        // Read from a file
        readFromFile("output.txt");
    }

    // Method to write data to a file
    private static void writeToFile(String fileName, String data) {
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(fileName))) {
            writer.write(data);
            System.out.println("Data written to " + fileName + " successfully!");
        } catch (IOException e) {
            System.out.println("Error occurred while writing to the file: " + e.getMessage());
            e.printStackTrace();
        }
    }

    // Method to read data from a file
    private static void readFromFile(String fileName) {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileName))) {
            String line;
            System.out.println("Reading from " + fileName + ":");
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            System.out.println("Error occurred while reading from the file: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
