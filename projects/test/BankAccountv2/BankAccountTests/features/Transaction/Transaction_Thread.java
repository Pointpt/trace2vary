/**
 * 
 */

/**
 * @author Jens
 *
 */
public class Transaction_Thread extends Thread {

	private Account destination;
	private int value;
	private Account source;
	public Transaction_Thread(Account source, Account destination, int value) {
		this.source = source;
		this.destination = destination;
		this.value = value;
	}
	
	@Override
	public void run() {
		new Transaction().transfer(source, destination, value);
		super.run();
	}
}
