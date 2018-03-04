import org.junit.Test;

import gov.nasa.jpf.util.test.TestJPF;

/**
 * TODO description
 */
public class AccountTest extends TestJPF {

	@Test
	public void accountTest() {
		if (verifyNoPropertyViolation()) {
			assertEquals(0, (new Account()).balance);
		}
	}
	
	@Test
	public void updateTest() {
		if (verifyNoPropertyViolation()) {
			Account a = new Account();
			a.update(100);
			assertEquals(100, a.balance);
		}
	}
	
	@Test
	public void undoUpdateTest() {
		if (verifyNoPropertyViolation()) {
			Account a = new Account();
			a.update(100);
			a.undoUpdate(100);
			assertEquals(0, a.balance);
		}
	}
}