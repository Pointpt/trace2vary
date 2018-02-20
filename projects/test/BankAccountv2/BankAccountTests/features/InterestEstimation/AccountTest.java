import gov.nasa.jpf.jvm.Verify;

/**
 * TODO description
 */
public class AccountTest {

	@Test
	public void estimatedInterestTest() {
		if (verifyNoPropertyViolation()) {
			FeatureModel.interestestimation_ = true;
			Account a = new Account();
			a.interest = 100;
			assertTrue(a.estimatedInterest(Verify.getInt(0, 100)) >= 0);
		}
	}
}