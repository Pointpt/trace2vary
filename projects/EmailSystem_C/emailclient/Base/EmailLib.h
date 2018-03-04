#define EMAIL  int

int initEmail();
int getEmailId(int handle);
void setEmailId(int handle, int value);
int getEmailFrom(int handle);
void setEmailFrom(int handle, int value);
int getEmailTo(int handle);
void setEmailTo(int handle, int value);
char* getEmailSubject(int handle);
void setEmailSubject(int handle, char* value);
char* getEmailBody(int handle);
void setEmailBody(int handle, char* value);
int isEncrypted(int handle);
void setEmailIsEncrypted(int handle, int value);
int getEmailEncryptionKey(int handle);
void setEmailEncryptionKey(int handle, int value);
int isSigned(int handle);
void setEmailIsSigned(int handle, int value);
int getEmailSignKey(int handle);
void setEmailSignKey(int handle, int value);
int isVerified(int handle);
void setEmailIsSignatureVerified(int handle, int value);
