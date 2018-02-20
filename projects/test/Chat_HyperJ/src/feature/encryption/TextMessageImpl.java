package feature.encryption;

public abstract class TextMessageImpl {

	private String content;
	private static EncryptionAlgorithm encryptionAlgorithm = new Rot13();

	public String getContent() {
		return encryptionAlgorithm.decrypt(content);
	}
	
	public void setContent(String content) {
		this.content = encryptionAlgorithm.encrypt(content);
	}
}
