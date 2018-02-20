import gov.nasa.jpf.util.test.TestJPF;

import org.junit.Test;

/**
 * TODO description
 */
public class AccountTest extends TestJPF {

	@Test
	public void updateTest_2() {
		if (verifyNoPropertyViolation()) {
			FeatureModel.dailylimit_ = true;
			Account a = new Account();
			a.update(10000);
			assertTrue(a.update(-900));
			assertFalse(a.update(-200));
		}
	}

}