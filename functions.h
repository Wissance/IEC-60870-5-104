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

unsigned int GetAPCIControlFieldFormat(struct APCIControlField* controlField);
void SetAPCIControlFieldFormat(unsigned int controlFieldFormat, struct APCIControlField* controlField);
unsigned short GetSendSequenceNumber(struct APCIControlField* controlField);
void SetSendSequenceNumber(unsigned short sendSequenceNumber, struct APCIControlField* controlField);
unsigned short GetReceiveSequenceNumber(struct APCIControlField* controlField);
void SetReceiveSequenceNumber(unsigned short receiveSequenceNumber, struct APCIControlField* controlField);
unsigned int GetAPCIControlInformation(struct APCIControlField* controlField);
void SetAPCIControlInformation(unsigned int controlInformation, struct APCIControlField* controlField);

#endif