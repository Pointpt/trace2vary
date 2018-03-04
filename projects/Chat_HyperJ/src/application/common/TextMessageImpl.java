package application.common;

/**
 * serializable message that can be send over the sockets between client and
 * server. 
 */
public class TextMessageImpl implements application.common.TextMessage {

	private static final long serialVersionUID = -9161595018411902079L;

	private String content;
	
	public TextMessageImpl() {
		this.content = null;
	}

	public String getContent() {
		return content;
	}
	
	public void setContent(String content) {
		this.content = content;
	}
	
}
