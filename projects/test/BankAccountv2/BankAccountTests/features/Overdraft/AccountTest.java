import gov.nasa.jpf.util.test.TestJPF;

import org.junit.Test;

/**
 * TODO description
 */
public class AccountTest extends TestJPF {

	public void update() {
		FeatureModel.overdraft_ = true;
		Account a = new Account();
		a.balance = -4900;
		assertTrue(a.update(-40));
		assertFalse(a.update(-100));
	}

}