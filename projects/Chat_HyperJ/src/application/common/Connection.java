package application.common;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * class for an individual connection to a client. allows to send messages to
 * this client and handles incoming messages.
 */
public abstract class Connection extends Thread {
	
	protected Socket socket;
	protected boolean connectionOpen = true;

	protected ObjectInputStream inputStream;
	protected ObjectOutputStream outputStream;

	protected String userName = null;

	/**
	 * Initializes the connection. Communication loop is executed when
	 * this thread is started.
	 */
	public Connection(Socket s) {
		this.socket = s;
		
		try {
			outputStream = new ObjectOutputStream(s.getOutputStream());
			inputStream = new ObjectInputStream((s.getInputStream()));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public String getUserName() {
		return userName;
	}
	
	public void setUserName(String userName) {
		this.userName = userName;
	}
	

	/**
	 * waits for incoming messages from the socket
	 */
	public void run() {
		// inform plugin that connection is established
		//for (ConnectionHandlerPlugin plugin : Application.getInstance().getPlugins(ConnectionHandlerPlugin.class))
		//	plugin.connectionEstablished(this);
		
		// do communication
		runCommunicationLoop();
		
		// inform plugin that connection is terminated
		//for (ConnectionHandlerPlugin plugin : Application.getInstance().getPlugins(ConnectionHandlerPlugin.class))
		//	plugin.connectionClosed(this);
	}
	
	protected abstract void runCommunicationLoop();

	/**
	 * sends a message to the client
	 * 
	 * @param line
	 *            text of the message
	 */
	public void send(Message msg) {
		if (outputStream == null || connectionOpen == false)
			return;
		
		try {
			synchronized (outputStream) {
				outputStream.writeObject(msg);
			}
			outputStream.flush();
		} catch (IOException e) {
			e.printStackTrace();
			connectionOpen = false;
		}

	}
	
	/**
	 * receives a message from the client (waits until message arrives).
	 * 
	 * @return
	 * @throws IOException
	 */
	public Message receive() {
		if (inputStream == null || connectionOpen == false)
			return null;
		
		Object msg = null;
		
		try {
			msg = inputStream.readObject();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
			connectionOpen = false;
		}
		
		return (Message) msg;
	}
	
	/**
	 * closes the connection. 
	 */
	public void close() {
		connectionOpen = false;
		
		try {
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
