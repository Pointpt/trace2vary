import gov.nasa.jpf.util.test.TestJPF;

import org.junit.Test;

/**
 * @author Jens
 *
 */
public class TransactionTest extends TestJPF{

	@Test
	public void testTransactionJPF() {
		if (verifyNoPropertyViolation()) {
			FeatureModel.transaction_ = true;
			testTransaction();
		}
	}
	
	public void testTransaction() {
		Account[] accounts = new Account[]{new Account(),new Account(),new Account()};
		for (Account a : accounts) {
			a.balance = 1000;
		}
		
		/* serially transactions */
		new Transaction().transfer(accounts[0], accounts[1], 100);
		new Transaction().transfer(accounts[1], accounts[2], 150);
		new Transaction().transfer(accounts[2], accounts[1], 250);
		
		/* parallel transactions */
//		Transaction_Thread t1 = new Transaction_Thread(accounts[0], accounts[1], 100);
//		Transaction_Thread t2 = new Transaction_Thread(accounts[1], accounts[2], 150);
//		Transaction_Thread t3 = new Transaction_Thread(accounts[2], accounts[1], 250);
//		
//		try {
//			t1.start();t1.join();
//			t2.start();t2.join();
//			t3.start();t3.join();
//		} catch (InterruptedException e) {
//	
//		}
		
		int i = 0;
		int counter = 0;
		for (Account a : accounts) {
			System.out.println("A" + counter++ + " : " + a.balance);
			i+=a.balance;
		}
		assertEquals(i, 1000 * accounts.length);
	}

}
