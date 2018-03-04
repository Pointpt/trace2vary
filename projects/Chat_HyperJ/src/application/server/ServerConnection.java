package application.server;

import java.net.Socket;

import application.common.Connection;
import application.common.Message;
import application.common.MessageFactory;
import application.common.TextMessage;


/**
 * class for an individual connection to a client. allows to send messages to
 * this client and handles incoming messages.
 */
public class ServerConnection extends Connection {

	private Server server;

	public ServerConnection(Socket s, Server server) {
		super(s);
		this.server = server;
	}

	/**
	 * waits for incoming messages from the socket
	 */
	protected void runCommunicationLoop() {
		try {
			// if no plugin has set the user name then we do here
			if (userName == null)
				userName = socket.getInetAddress().toString();
			
			// inform others about entering chat
			server.broadcast(MessageFactory.newTextMessage("" + userName + " has joined."));
			
			// do chatting
			while (connectionOpen) {
				Message msg = receive();
				
				if (msg != null)
					handleIncomingMessage(msg);
			}
		} 
		finally {
			// clean up
			server.removeConnection(this);
			server.broadcast(MessageFactory.newTextMessage("" + userName + " has left."));
			
			close();
		}
	}

	/**
	 * decides what to do with incoming messages
	 * 
	 * @param name
	 *            name of the client
	 * @param msg
	 *            received message
	 */
	private void handleIncomingMessage(Message msg) {
		if (msg instanceof TextMessage) {
			TextMessage txtMsg = (TextMessage) msg;
			txtMsg.setContent(getUserName() + " - " + txtMsg.getContent());
			
			//for (MessageTransferHandlerPlugin plugin : Application.getInstance().getPlugins(MessageTransferHandlerPlugin.class))
			//	plugin.messageReceived(txtMsg);
			
			server.broadcast(txtMsg);
		}
	}
	
}
