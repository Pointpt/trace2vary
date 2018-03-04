
/**
 * TODO description
 */
public class Account {
	
	private boolean lock = false;
	
	void lock() {
		lock = true;
	}
	
	void unLock() {
		lock = false;
	}
	
	boolean isLocked() {
		return lock;
	}
}