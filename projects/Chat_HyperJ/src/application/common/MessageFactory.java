package application.common;

public class MessageFactory {

	public static TextMessage newTextMessage(String content) {
		TextMessage msg = new TextMessageImpl();
		msg.setContent(content);
		
		return msg;
	}
	
}
