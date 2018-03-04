#include <stdlib.h>
#include "ClientLib.h"
int __ste_Client_counter = 0;
int initClient() {
	if (__ste_Client_counter < 3) {
		return ++__ste_Client_counter;
	} else {
		return -1;
	}
}
char* __ste_client_name0 = 0;
char* __ste_client_name1 = 0;
char* __ste_client_name2 = 0;

char* getClientName(int handle) {
	if (handle == 1) {
		return __ste_client_name0;
	} else if (handle == 2) {
		return __ste_client_name1;
	} else if (handle == 3) {
		return __ste_client_name2;
	} else {
		return NULL;
	}
}
void setClientName(int handle, char* value) {
	if (handle == 1) {
		__ste_client_name0 = value;
	} else if (handle == 2) {
		__ste_client_name1 = value;
	} else if (handle == 3) {
		__ste_client_name2 = value;
	} 
}
int __ste_client_outbuffer0 = 0;
int __ste_client_outbuffer1 = 0;
int __ste_client_outbuffer2 = 0;
int __ste_client_outbuffer3 = 0;

int getClientOutbuffer(int handle) {
	if (handle == 1) {
		return __ste_client_outbuffer0;
	} else if (handle == 2) {
		return __ste_client_outbuffer1;
	} else if (handle == 3) {
		return __ste_client_outbuffer2;
	} else {
		return 0;
	}
}
void setClientOutbuffer(int handle, int value) {
	if (handle == 1) {
		__ste_client_outbuffer0 = value;
	} else if (handle == 2) {
		__ste_client_outbuffer1 = value;
	} else if (handle == 3) {
		__ste_client_outbuffer2 = value;
	}
}


int __ste_ClientAddressBook_size0 = 0;
int __ste_ClientAddressBook_size1 = 0;
int __ste_ClientAddressBook_size2 = 0;

int getClientAddressBookSize(int handle){
	if (handle == 1) {
		return __ste_ClientAddressBook_size0;
	} else if (handle == 2) {
		return __ste_ClientAddressBook_size1;
	} else if (handle == 3) {
		return __ste_ClientAddressBook_size2;
	} else {
		return 0;
	}
}
void setClientAddressBookSize(int handle, int value) {
	if (handle == 1) {
		__ste_ClientAddressBook_size0 = value;
	} else if (handle == 2) {
		__ste_ClientAddressBook_size1 = value;
	} else if (handle == 3) {
		__ste_ClientAddressBook_size2 = value;
	}
}
int createClientAddressBookEntry(int handle){
    int size = getClientAddressBookSize(handle);
	if (size < 3) {
	    setClientAddressBookSize(handle, size + 1);
		return size + 1;
	} else return -1;
}

int __ste_Client_AddressBook0_Alias0 = 0;
int __ste_Client_AddressBook0_Alias1 = 0;
int __ste_Client_AddressBook0_Alias2 = 0;
int __ste_Client_AddressBook1_Alias0 = 0;
int __ste_Client_AddressBook1_Alias1 = 0;
int __ste_Client_AddressBook1_Alias2 = 0;
int __ste_Client_AddressBook2_Alias0 = 0;
int __ste_Client_AddressBook2_Alias1 = 0;
int __ste_Client_AddressBook2_Alias2 = 0;

int getClientAddressBookAlias(int handle, int index) {
	if (handle == 1) {
		if (index == 0) {
			return __ste_Client_AddressBook0_Alias0;
		} else if (index == 1) {
			return __ste_Client_AddressBook0_Alias1;
		} else if (index == 2) {
			return __ste_Client_AddressBook0_Alias2;
		} else {
			return 0;
		}
	} else if (handle == 2) {
		if (index == 0) {
			return __ste_Client_AddressBook1_Alias0;
		} else if (index == 1) {
			return __ste_Client_AddressBook1_Alias1;
		} else if (index == 2) {
			return __ste_Client_AddressBook1_Alias2;
		} else {
			return 0;
		}
	} else if (handle == 3) {
		if (index == 0) {
			return __ste_Client_AddressBook2_Alias0;
		} else if (index == 1) {
			return __ste_Client_AddressBook2_Alias1;
		} else if (index == 2) {
			return __ste_Client_AddressBook2_Alias2;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

int findClientAddressBookAlias(int handle, int userid) {
	if (handle == 1) {
		if (userid == __ste_Client_AddressBook0_Alias0) {
			return 0;
		} else if (userid == __ste_Client_AddressBook0_Alias1) {
			return 1;
		} else if (userid == __ste_Client_AddressBook0_Alias2) {
			return 2;
		} else {
			return -1;
		}
	} else if (handle == 2) {
		if (userid == __ste_Client_AddressBook1_Alias0) {
			return 0;
		} else if (userid == __ste_Client_AddressBook1_Alias1) {
			return 1;
		} else if (userid == __ste_Client_AddressBook1_Alias2) {
			return 2;
		} else {
			return -1;
		}
	} else if (handle == 3) {
		if (userid == __ste_Client_AddressBook2_Alias0) {
			return 0;
		} else if (userid == __ste_Client_AddressBook2_Alias1) {
			return 1;
		} else if (userid == __ste_Client_AddressBook2_Alias2) {
			return 2;
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

void setClientAddressBookAlias(int handle, int index, int value) {
	if (handle == 1) {
		if (index == 0) {
			__ste_Client_AddressBook0_Alias0 = value;
		} else if (index == 1) {
			__ste_Client_AddressBook0_Alias1 = value;
		} else if (index == 2) {
			__ste_Client_AddressBook0_Alias2 = value;
		}
	} else if (handle == 2) {
		if (index == 0) {
			__ste_Client_AddressBook1_Alias0 = value;
		} else if (index == 1) {
			__ste_Client_AddressBook1_Alias1 = value;
		} else if (index == 2) {
			__ste_Client_AddressBook1_Alias2 = value;
		}
	} else if (handle == 3) {
		if (index == 0) {
			__ste_Client_AddressBook2_Alias0 = value;
		} else if (index == 1) {
			__ste_Client_AddressBook2_Alias1 = value;
		} else if (index == 2) {
			__ste_Client_AddressBook2_Alias2 = value;
		}
	} 
}
int __ste_Client_AddressBook0_Address0 = 0;
int __ste_Client_AddressBook0_Address1 = 0;
int __ste_Client_AddressBook0_Address2 = 0;
int __ste_Client_AddressBook1_Address0 = 0;
int __ste_Client_AddressBook1_Address1 = 0;
int __ste_Client_AddressBook1_Address2 = 0;
int __ste_Client_AddressBook2_Address0 = 0;
int __ste_Client_AddressBook2_Address1 = 0;
int __ste_Client_AddressBook2_Address2 = 0;

int getClientAddressBookAddress(int handle, int index) {
	if (handle == 1) {
		if (index == 0) {
			return __ste_Client_AddressBook0_Address0;
		} else if (index == 1) {
			return __ste_Client_AddressBook0_Address1;
		} else if (index == 2) {
			return __ste_Client_AddressBook0_Address2;
		} else {
			return 0;
		}
	} else if (handle == 2) {
		if (index == 0) {
			return __ste_Client_AddressBook1_Address0;
		} else if (index == 1) {
			return __ste_Client_AddressBook1_Address1;
		} else if (index == 2) {
			return __ste_Client_AddressBook1_Address2;
		} else {
			return 0;
		}
	} else if (handle == 3) {
		if (index == 0) {
			return __ste_Client_AddressBook2_Address0;
		} else if (index == 1) {
			return __ste_Client_AddressBook2_Address1;
		} else if (index == 2) {
			return __ste_Client_AddressBook2_Address2;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}
void setClientAddressBookAddress(int handle, int index, int value) {
	if (handle == 1) {
		if (index == 0) {
			__ste_Client_AddressBook0_Address0 = value;
		} else if (index == 1) {
			__ste_Client_AddressBook0_Address1 = value;
		} else if (index == 2) {
			__ste_Client_AddressBook0_Address2 = value;
		}
	} else if (handle == 2) {
		if (index == 0) {
			__ste_Client_AddressBook1_Address0 = value;
		} else if (index == 1) {
			__ste_Client_AddressBook1_Address1 = value;
		} else if (index == 2) {
			__ste_Client_AddressBook1_Address2 = value;
		}
	} else if (handle == 3) {
		if (index == 0) {
			__ste_Client_AddressBook2_Address0 = value;
		} else if (index == 1) {
			__ste_Client_AddressBook2_Address1 = value;
		} else if (index == 2) {
			__ste_Client_AddressBook2_Address2 = value;
		}
	} 
}
int __ste_client_autoResponse0 = 0;
int __ste_client_autoResponse1 = 0;
int __ste_client_autoResponse2 = 0;

int getClientAutoResponse(int handle) {
	if (handle == 1) {
		return __ste_client_autoResponse0;
	} else if (handle == 2) {
		return __ste_client_autoResponse1;
	} else if (handle == 3) {
		return __ste_client_autoResponse2;
	} else {
		return -1;
	}
}
void setClientAutoResponse(int handle, int value) {
	if (handle == 1) {
		__ste_client_autoResponse0 = value;
	} else if (handle == 2) {
		__ste_client_autoResponse1 = value;
	} else if (handle == 3) {
		__ste_client_autoResponse2 = value;
	} 
}
int __ste_client_privateKey0 = 0;
int __ste_client_privateKey1 = 0;
int __ste_client_privateKey2 = 0;

int getClientPrivateKey(int handle) {
	if (handle == 1) {
		return __ste_client_privateKey0;
	} else if (handle == 2) {
		return __ste_client_privateKey1;
	} else if (handle == 3) {
		return __ste_client_privateKey2;
	} else {
		return 0;
	}
}
void setClientPrivateKey(int handle, int value) {
	if (handle == 1) {
		__ste_client_privateKey0 = value;
	} else if (handle == 2) {
		__ste_client_privateKey1 = value;
	} else if (handle == 3) {
		__ste_client_privateKey2 = value;
	} 
}
int __ste_ClientKeyring_size0 = 0;
int __ste_ClientKeyring_size1 = 0;
int __ste_ClientKeyring_size2 = 0;

int getClientKeyringSize(int handle){
	if (handle == 1) {
		return __ste_ClientKeyring_size0;
	} else if (handle == 2) {
		return __ste_ClientKeyring_size1;
	} else if (handle == 3) {
		return __ste_ClientKeyring_size2;
	} else {
		return 0;
	}
}
void setClientKeyringSize(int handle, int value) {
	if (handle == 1) {
		__ste_ClientKeyring_size0 = value;
	} else if (handle == 2) {
		__ste_ClientKeyring_size1 = value;
	} else if (handle == 3) {
		__ste_ClientKeyring_size2 = value;
	} 
}
int createClientKeyringEntry(int handle){
    int size = getClientKeyringSize(handle);
	if (size < 2) {
	    setClientKeyringSize(handle, size + 1);
		return size + 1;
	} else return -1;
}
int __ste_Client_Keyring0_User0 = 0;
int __ste_Client_Keyring0_User1 = 0;
int __ste_Client_Keyring0_User2 = 0;
int __ste_Client_Keyring1_User0 = 0;
int __ste_Client_Keyring1_User1 = 0;
int __ste_Client_Keyring1_User2 = 0;
int __ste_Client_Keyring2_User0 = 0;
int __ste_Client_Keyring2_User1 = 0;
int __ste_Client_Keyring2_User2 = 0;

int getClientKeyringUser(int handle, int index) {
	if (handle == 1) {
		if (index == 0) {
			return __ste_Client_Keyring0_User0;
		} else if (index == 1) {
			return __ste_Client_Keyring0_User1;
		} /*else if (index == 2) {
			return __ste_Client_Keyring0_User2;
		} */else {
			return 0;
		}
	} else if (handle == 2) {
		if (index == 0) {
			return __ste_Client_Keyring1_User0;
		} else if (index == 1) {
			return __ste_Client_Keyring1_User1;
		} /*else if (index == 2) {
			return __ste_Client_Keyring1_User2;
		} */else {
			return 0;
		}
	} else if (handle == 3) {
		if (index == 0) {
			return __ste_Client_Keyring2_User0;
		} else if (index == 1) {
			return __ste_Client_Keyring2_User1;
		} /*else if (index == 2) {
			return __ste_Client_Keyring2_User2;
		} */else {
			return 0;
		}
	} else {
		return 0;
	}
}




void setClientKeyringUser(int handle, int index, int value) {
	if (handle == 1) {
		if (index == 0) {
			__ste_Client_Keyring0_User0 = value;
		} else if (index == 1) {
			__ste_Client_Keyring0_User1 = value;
		}/* else if (index == 2) {
			__ste_Client_Keyring0_User2 = value;
		}*/
	} else if (handle == 2) {
		if (index == 0) {
			__ste_Client_Keyring1_User0 = value;
		} else if (index == 1) {
			__ste_Client_Keyring1_User1 = value;
		}/* else if (index == 2) {
			__ste_Client_Keyring1_User2 = value;
		}*/
	} else if (handle == 3) {
		if (index == 0) {
			__ste_Client_Keyring2_User0 = value;
		} else if (index == 1) {
			__ste_Client_Keyring2_User1 = value;
		}/* else if (index == 2) {
			__ste_Client_Keyring2_User2 = value;
		}*/
	}
}
int __ste_Client_Keyring0_PublicKey0 = 0;
int __ste_Client_Keyring0_PublicKey1 = 0;
int __ste_Client_Keyring0_PublicKey2 = 0;
int __ste_Client_Keyring1_PublicKey0 = 0;
int __ste_Client_Keyring1_PublicKey1 = 0;
int __ste_Client_Keyring1_PublicKey2 = 0;
int __ste_Client_Keyring2_PublicKey0 = 0;
int __ste_Client_Keyring2_PublicKey1 = 0;
int __ste_Client_Keyring2_PublicKey2 = 0;

int getClientKeyringPublicKey(int handle, int index) {
	if (handle == 1) {
		if (index == 0) {
			return __ste_Client_Keyring0_PublicKey0;
		} else if (index == 1) {
			return __ste_Client_Keyring0_PublicKey1;
		} /*else if (index == 2) {
			return __ste_Client_Keyring0_PublicKey2;
		} */else {
			return 0;
		}
	} else if (handle == 2) {
		if (index == 0) {
			return __ste_Client_Keyring1_PublicKey0;
		} else if (index == 1) {
			return __ste_Client_Keyring1_PublicKey1;
		}/* else if (index == 2) {
			return __ste_Client_Keyring1_PublicKey2;
		}*/ else {
			return 0;
		}
	} else if (handle == 3) {
		if (index == 0) {
			return __ste_Client_Keyring2_PublicKey0;
		} else if (index == 1) {
			return __ste_Client_Keyring2_PublicKey1;
		}/* else if (index == 2) {
			return __ste_Client_Keyring2_PublicKey2;
		}*/ else {
			return 0;
		}
	} else {
		return 0;
	}
}

int findPublicKey(int handle, int userid) {

	if (handle == 1) {
		if (userid == __ste_Client_Keyring0_User0) {
			return __ste_Client_Keyring0_PublicKey0;
		} else if (userid == __ste_Client_Keyring0_User1) {
			return __ste_Client_Keyring0_PublicKey1;
		}/* else if (userid == __ste_Client_Keyring0_User2) {
			return __ste_Client_Keyring0_PublicKey2;
		} */else {
			return 0;
		}
	} else if (handle == 2) {
		if (userid == __ste_Client_Keyring1_User0) {
			return __ste_Client_Keyring1_PublicKey0;
		} else if (userid == __ste_Client_Keyring1_User1) {
			return __ste_Client_Keyring1_PublicKey1;
		} /*else if (userid == __ste_Client_Keyring1_User2) {
			return __ste_Client_Keyring1_PublicKey2;
		} */else {
			return 0;
		}
	} else if (handle == 3) {
		if (userid == __ste_Client_Keyring2_User0) {
			return __ste_Client_Keyring2_PublicKey0;
		} else if (userid == __ste_Client_Keyring2_User1) {
			return __ste_Client_Keyring2_PublicKey1;
		} /*else if (userid == __ste_Client_Keyring2_User2) {
			return __ste_Client_Keyring2_PublicKey2;
		} */else {
			return 0;
		}
	} else {
		return 0;
	}
}

void setClientKeyringPublicKey(int handle, int index, int value) {
	if (handle == 1) {
		if (index == 0) {
			__ste_Client_Keyring0_PublicKey0 = value;
		} else if (index == 1) {
			__ste_Client_Keyring0_PublicKey1 = value;
		} /*else if (index == 2) {
			__ste_Client_Keyring0_PublicKey2 = value;
		}*/
	} else if (handle == 2) {
		if (index == 0) {
			__ste_Client_Keyring1_PublicKey0 = value;
		} else if (index == 1) {
			__ste_Client_Keyring1_PublicKey1 = value;
		} /*else if (index == 2) {
			__ste_Client_Keyring1_PublicKey2 = value;
		}*/
	} else if (handle == 3) {
		if (index == 0) {
			__ste_Client_Keyring2_PublicKey0 = value;
		} else if (index == 1) {
			__ste_Client_Keyring2_PublicKey1 = value;
		} /*else if (index == 2) {
			__ste_Client_Keyring2_PublicKey2 = value;
		}*/
	}
}
int __ste_client_forwardReceiver0 =0;
int __ste_client_forwardReceiver1 =0;
int __ste_client_forwardReceiver2 =0;
int __ste_client_forwardReceiver3 =0;
int getClientForwardReceiver(int handle) {
	if (handle == 1) {
		return __ste_client_forwardReceiver0;
	} else if (handle == 2) {
		return __ste_client_forwardReceiver1;
	} else if (handle == 3) {
		return __ste_client_forwardReceiver2;
	} else {
		return 0;
	}
}
void setClientForwardReceiver(int handle, int value) {
	if (handle == 1) {
		__ste_client_forwardReceiver0 = value;
	} else if (handle == 2) {
		__ste_client_forwardReceiver1 = value;
	} else if (handle == 3) {
		__ste_client_forwardReceiver2 = value;
	}
}
int __ste_client_idCounter0 = 0;
int __ste_client_idCounter1 = 0;
int __ste_client_idCounter2 = 0;

int getClientId(int handle) {
	if (handle == 1) {
		return __ste_client_idCounter0;
	} else if (handle == 2) {
		return __ste_client_idCounter1;
	} else if (handle == 3) {
		return __ste_client_idCounter2;
	} else {
		return 0;
	}
}
void setClientId(int handle, int value) {
	if (handle == 1) {
		__ste_client_idCounter0 = value;
	} else if (handle == 2) {
		__ste_client_idCounter1 = value;
	} else if (handle == 3) {
		__ste_client_idCounter2 = value;
	}
}
