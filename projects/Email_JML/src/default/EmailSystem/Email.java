package EmailSystem; public  class Email {
	protected int id;

	protected String subject;

	protected String body;

	protected Client from;

	protected String to;

	static int emailCounter = 1;



	public Email(int id) {
		this.id = id;
	}



	static Email createEmail(Client from, String to, String subject, String body) {
		Email msg = new Email(emailCounter++);
		msg.setEmailFrom(from);
		msg.setEmailTo(to);
		msg.setEmailSubject(subject);
		msg.setEmailBody(body);
		return msg;
	}



	private /*@pure@*/ boolean isReadable__wrappee__Keys  () {
		return true;
	}



	 /*@pure@*/ boolean  isReadable() {
		if (!isEncrypted())
			return isReadable__wrappee__Keys();
		else
			return false;
	}



	private static void printMail__wrappee__Keys  (Email msg) {
		Util.prompt("ID:  " + msg.getId());
		Util.prompt("FROM: " + msg.getEmailFrom().getId());
		Util.prompt("TO: " + msg.getEmailTo());
		Util.prompt("SUBJECT: " + msg.getEmailSubject());
		Util.prompt("IS_READABLE " + msg.isReadable());
		Util.prompt("BODY: " + msg.getEmailBody());
	}



	private static void printMail__wrappee__Addressbook  (Email msg) {
		printMail__wrappee__Keys(msg);
		Util.prompt("ENCRYPTED " + msg.isEncrypted());
		// Util.prompt("ENCRYPTION KEY  "+ msg.getEmailEncryptionKey());
	}



	private static void printMail__wrappee__Forward  (Email msg) {
		printMail__wrappee__Addressbook(msg);
		Util.prompt("SIGNED " + msg.isSigned());
		Util.prompt("SIGNATURE " + msg.getEmailSignKey());
	}



	static void printMail(Email msg) {
		printMail__wrappee__Forward(msg);
		Util.prompt("SIGNATURE VERIFIED " + msg.isSignatureVerified());
	}



	Email cloneEmail(Email msg) {
		try {
			return (Email) this.clone();
		} catch (CloneNotSupportedException e) {
			throw new Error("Clone not supported");
		}
	}



	 /*@pure@*/ Client getEmailFrom() {
		return from;
	}



	int getId() {
		return id;
	}



	String getEmailSubject() {
		return subject;
	}



	String getEmailTo() {
		return to;
	}



	void setEmailBody(String value) {
		body = value;
	}



	void setEmailFrom(Client value) {
		this.from = value;
	}



	void setEmailSubject(String value) {
		this.subject = value;
	}



	void setEmailTo(String value) {
		to = value;
	}



	String getEmailBody() {
		return body;
	}

	protected boolean isEncrypted;

	protected int encryptionKey;



	 /*@pure@*/ boolean  isEncrypted() {
		return isEncrypted;
	}



	void setEmailIsEncrypted(boolean value) {
		isEncrypted = value;
	}



	void setEmailEncryptionKey(int value) {
		this.encryptionKey = value;
	}



	 /*@pure@*/ int getEmailEncryptionKey() {
		return encryptionKey;
	}

	protected boolean signed;

	protected int signkey;



	void setEmailIsSigned(boolean value) {
		signed = value;
	}



	void setEmailSignKey(int value) {
		signkey = value;
	}



	boolean isSigned() {
		return signed;
	}



	 /*@pure@*/ int getEmailSignKey() {
		return signkey;
	}

	protected boolean isSignatureVerified;



	 /*@pure@*/ boolean isSignatureVerified() {
		return isSignatureVerified;
	}



	void setIsSignatureVerified(boolean value) {
		this.isSignatureVerified = value;
	}


}
