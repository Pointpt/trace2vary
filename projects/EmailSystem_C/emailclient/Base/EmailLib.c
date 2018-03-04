#include <stdlib.h>
#include "EmailLib.h"
int __ste_Email_counter = 0;
int initEmail() {
	if (__ste_Email_counter < 2) {
		return ++__ste_Email_counter;
	} else {
		return -1;
	}
}
int __ste_email_id0 = 0;
int __ste_email_id1 = 0;
int getEmailId(int handle) {
	if (handle == 1) {
		return __ste_email_id0;
	} else if (handle == 2) {
		return __ste_email_id1;
	} else {
		return 0;
	}
}
void setEmailId(int handle, int value) {
	if (handle == 1) {
		__ste_email_id0 = value;
	} else if (handle == 2) {
		__ste_email_id1 = value;
	}
}
int __ste_email_from0 = 0;
int __ste_email_from1 = 0;
int getEmailFrom(int handle) {
	if (handle == 1) {
		return __ste_email_from0;
	} else if (handle == 2) {
		return __ste_email_from1;
	} else {
		return 0;
	}
}
void setEmailFrom(int handle, int value) {
	if (handle == 1) {
		__ste_email_from0 = value;
	} else if (handle == 2) {
		__ste_email_from1 = value;
	}
}
int __ste_email_to0 = 0;
int __ste_email_to1 = 0;
int getEmailTo(int handle) {
	if (handle == 1) {
		return __ste_email_to0;
	} else if (handle == 2) {
		return __ste_email_to1;
	} else {
		return 0;
	}
}
void setEmailTo(int handle, int value) {
	if (handle == 1) {
		__ste_email_to0 = value;
	} else if (handle == 2) {
		__ste_email_to1 = value;
	}
}
char* __ste_email_subject0;
char* __ste_email_subject1;
char* getEmailSubject(int handle) {
	if (handle == 1) {
		return __ste_email_subject0;
	} else if (handle == 2) {
		return __ste_email_subject1;
	} else {
		return NULL;
	}
}
void setEmailSubject(int handle, char* value) {
	if (handle == 1) {
		__ste_email_subject0 = value;
	} else if (handle == 2) {
		__ste_email_subject1 = value;
	}
}
char* __ste_email_body0 = 0;
char* __ste_email_body1 = 0;
char* getEmailBody(int handle) {
	if (handle == 1) {
		return __ste_email_body0;
	} else if (handle == 2) {
		return __ste_email_body1;
	} else {
		return NULL;
	}
}
void setEmailBody(int handle, char* value) {
	if (handle == 1) {
		__ste_email_body0 = value;
	} else if (handle == 2) {
		__ste_email_body1 = value;
	}
}
int __ste_email_isEncrypted0 = 0;
int __ste_email_isEncrypted1 = 0;
int isEncrypted(int handle) {
	if (handle == 1) {
		return __ste_email_isEncrypted0;
	} else if (handle == 2) {
		return __ste_email_isEncrypted1;
	} else {
		return 0;
	}
}
void setEmailIsEncrypted(int handle, int value) {
	if (handle == 1) {
		__ste_email_isEncrypted0 = value;
	} else if (handle == 2) {
		__ste_email_isEncrypted1 = value;
	}
}
int __ste_email_encryptionKey0 = 0;
int __ste_email_encryptionKey1 = 0;
int getEmailEncryptionKey(int handle) {
	if (handle == 1) {
		return __ste_email_encryptionKey0;
	} else if (handle == 2) {
		return __ste_email_encryptionKey1;
	} else {
		return 0;
	}
}
void setEmailEncryptionKey(int handle, int value) {
	if (handle == 1) {
		__ste_email_encryptionKey0 = value;
	} else if (handle == 2) {
		__ste_email_encryptionKey1 = value;
	}
}
int __ste_email_isSigned0 = 0;
int __ste_email_isSigned1 = 0;
int isSigned(int handle) {
	if (handle == 1) {
		return __ste_email_isSigned0;
	} else if (handle == 2) {
		return __ste_email_isSigned1;
	} else {
		return 0;
	}
}
void setEmailIsSigned(int handle, int value) {
	if (handle == 1) {
		__ste_email_isSigned0 = value;
	} else if (handle == 2) {
		__ste_email_isSigned1 = value;
	}
}
int __ste_email_signKey0 = 0;
int __ste_email_signKey1 = 0;
int getEmailSignKey(int handle) {
	if (handle == 1) {
		return __ste_email_signKey0;
	} else if (handle == 2) {
		return __ste_email_signKey1;
	} else {
		return 0;
	}
}
void setEmailSignKey(int handle, int value) {
	if (handle == 1) {
		__ste_email_signKey0 = value;
	} else if (handle == 2) {
		__ste_email_signKey1 = value;
	}
}
int __ste_email_isSignatureVerified0;
int __ste_email_isSignatureVerified1;
int isVerified(int handle) {
	if (handle == 1) {
		return __ste_email_isSignatureVerified0;
	} else if (handle == 2) {
		return __ste_email_isSignatureVerified1;
	} else {
		return 0;
	}
}
void setEmailIsSignatureVerified(int handle, int value) {
	if (handle == 1) {
		__ste_email_isSignatureVerified0 = value;
	} else if (handle == 2) {
		__ste_email_isSignatureVerified1 = value;
	}
}
