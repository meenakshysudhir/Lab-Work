import java.io.*;
import java.util.Scanner;
//READING
public class Q2
{
    public static void main(String[] args)
    {
        try(BufferedReader reader = new BufferedReader(new FileReader("File2.txt")))
        {
            String data;
            int c = 1;
            while((data = reader.readLine()) != null)
            {
                System.out.println(c + ". " + data);
                c++;
            }
        }
        catch(FileNotFoundException e)
        {
            System.out.println("Error Occured!");
            e.printStackTrace();
        }
        catch(IOException e)
        {
            System.out.println("Error while reading from file");
            e.printStackTrace();
        }
    }
}