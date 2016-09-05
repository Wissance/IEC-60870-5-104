#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define APCI_CONTROL_FIELD_FORMAT_I 0U
#define APCI_CONTROL_FIELD_FORMAT_S 1U
#define APCI_CONTROL_FIELD_FORMAT_U 2U

#define APCI_CONTROL_INFORMATION_STARTDT_ACT 0U
#define APCI_CONTROL_INFORMATION_STARTDT_CON 1U

#define APCI_CONTROL_INFORMATION_STOPDT_ACT 2U
#define APCI_CONTROL_INFORMATION_STOPDT_CON 3U

#define APCI_CONTROL_INFORMATION_TESTFR_ACT 4U
#define APCI_CONTROL_INFORMATION_TESTFR_CON 5U

struct APCIControlField;

unsigned int getAPCIControlFieldFormat(struct APCIControlField* controlField);
void setAPCIControlFieldFormat(unsigned int controlFieldFormat, struct APCIControlField* controlField);
unsigned short getSendSequenceNumber(struct APCIControlField* controlField);
void setSendSequenceNumber(unsigned short sendSequenceNumber, struct APCIControlField* controlField);
unsigned short getReceiveSequenceNumber(struct APCIControlField* controlField);
void setReceiveSequenceNumber(unsigned short receiveSequenceNumber, struct APCIControlField* controlField);
unsigned int getAPCIControlInformation(struct APCIControlField* controlField);
void setAPCIControlInformation(unsigned int controlInformation, struct APCIControlField* controlField);

unsigned int checkSocketForReadability(SOCKET endpoint, long seconds, long microseconds);
unsigned int checkSocketForWritability(SOCKET endpoint, long seconds, long microseconds);
unsigned int checkSocketForErrors(SOCKET endpoint, long seconds, long microseconds);
unsigned int readFromSocket(SOCKET endpoint, unsigned char* buffer, unsigned int numberOfBytesToRead, unsigned int* numberOfBytesRead);
unsigned int writeToSocket(SOCKET endpoint, const unsigned char* buffer, unsigned int numberOfBytesToWrite, unsigned int* numberOfBytesWritten);
unsigned int receiveAPDU(SOCKET endpoint, unsigned char* APDUBuffer);
unsigned int sendAPDU(SOCKET endpoint, const unsigned char* APDUBuffer);
bool ConnectToControlledStation(const char* IPAddress, unsigned short port, SOCKET* clientSocket);
#endif