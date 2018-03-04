package feature.ui.gui;

import java.io.IOException;

import application.client.ClientConnection;

public class Client {
	
	public Client(String host, int port) throws IOException {
	}

	private void startUI(ClientConnection client) {
		new GuiImpl("GUI Client", client);
	}

}
