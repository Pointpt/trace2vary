import gov.nasa.jpf.util.test.TestJPF;

import org.junit.Test;

/**
 * TODO description
 */
public class AccountTest extends TestJPF {

	@Test
	public void creditTest() {
		if (verifyNoPropertyViolation()) {
			FeatureModel.creditworthiness_ = true;
			Account a = new Account();
			a.update(100);
			assertTrue(a.credit(100));
			assertFalse(a.credit(101));
		}
	}

}