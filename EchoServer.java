/*
SYST44288
November 4, 2018
Students: Pavel K., Herit G.
Professor: Christina R.
*/

import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.io.InputStreamReader;

public class EchoServer
{
	public static void main (String args[])
	{
		try
		{
			/*Open the port*/
			ServerSocket ss = new ServerSocket(7777);
			while (true)
			{
				/*Accept new client connection*/
				new ClientConnection(ss.accept());
			}
		}
		catch (IOException ioe)
        {
            System.err.println(ioe);
        }
	}
}

class ClientConnection extends Thread
{
	Socket client;
	public ClientConnection(Socket socket)
	{
		client = socket;
		this.start();
	}

	public void run()
	{
		try 
		{
			System.out.println("New client connected");		
			while (!client.isClosed())
			{
				BufferedReader dis = new BufferedReader(new InputStreamReader(client.getInputStream()));
                PrintWriter dos = new PrintWriter(client.getOutputStream(),true);
                
                String userInput;
                /*Read input and send it back to the client*/
                while (null != (userInput = dis.readLine()))
                {
                    dos.println("Server: " + userInput);
                }
                client.close();
			}
			System.out.println("Client disconnected");
		} 
		catch (IOException ioe) 
		{
			System.err.println(ioe);
		}
	}
}