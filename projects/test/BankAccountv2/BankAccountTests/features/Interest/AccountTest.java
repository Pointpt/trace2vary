import gov.nasa.jpf.jvm.Verify;

/**
 * TODO description
 */
public class AccountTest {

	@Test
	public void calculateInterestTest() {
		if (verifyNoPropertyViolation()) {
			if (!FeatureModel.interest()) return;
			Account a = new Account();
			a.balance = Verify.getInt(a.OVERDRAFT_LIMIT,100);
			if (a.balance >= 0) {
				assertTrue(a.calculateInterest() >= 0);
			} else {
				assertTrue(a.calculateInterest() <= 0);
			}
		}
	}
}