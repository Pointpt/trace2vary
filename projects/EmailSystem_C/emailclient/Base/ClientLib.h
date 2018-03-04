#define CLIENT  int

int initClient();
char* getClientName(int handle);
void setClientName(int handle, char* value);
int getClientOutbuffer(int handle);
void setClientOutbuffer(int handle, int value);
int getClientAddressBookSize(int handle);
void setClientAddressBookSize(int handle, int value);
int createClientAddressBookEntry(int handle);
int getClientAddressBookAlias(int handle, int index);
void setClientAddressBookAlias(int handle, int index, int value);
int getClientAddressBookAddress(int handle, int index);
void setClientAddressBookAddress(int handle, int index, int value);

int getClientAutoResponse(int handle);
void setClientAutoResponse(int handle, int value);
int getClientPrivateKey(int handle);
void setClientPrivateKey(int handle, int value);
int getClientKeyringSize(int handle);
int createClientKeyringEntry(int handle);
int getClientKeyringUser(int handle, int index);
void setClientKeyringUser(int handle, int index, int value);
int getClientKeyringPublicKey(int handle, int index);
void setClientKeyringPublicKey(int handle, int index, int value);
int getClientForwardReceiver(int handle);
void setClientForwardReceiver(int handle, int value);
int getClientId(int handle);
void setClientId(int handle, int value);
int findPublicKey(int handle, int userid);
int findClientAddressBookAlias(int handle, int userid);
