package feature.encryption;

import java.io.Serializable;

/**
 * Interface for an encryption algorithm.
 */
public interface EncryptionAlgorithm extends Serializable {
	
	/**
	 * Encrypts the plain text.
	 * 
	 * @param content content to be encrypted
	 * @return encrypted content
	 */
	public String encrypt(String content);
	
	/**
	 * Decrypts the encrypted text.
	 * 
	 * @param content text to be decrypted
	 * @return decrypted content
	 */
	public String decrypt(String content);

}
