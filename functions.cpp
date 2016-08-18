#include "functions.h"
#include "types.h"

unsigned int GetAPCIControlFieldFormat(struct APCIControlField* controlField) {
	if (!(controlField->octet1 & 1))
		return APCI_CONTROL_FIELD_FORMAT_I;

	if (!(controlField->octet1 & 2))
		return APCI_CONTROL_FIELD_FORMAT_S;

	return APCI_CONTROL_FIELD_FORMAT_U;
}

void SetAPCIControlFieldFormat(unsigned int controlFieldFormat, struct APCIControlField* controlField) {
	switch (controlFieldFormat) {
	case APCI_CONTROL_FIELD_FORMAT_I:
		controlField->octet1 >>= 1;
		controlField->octet1 <<= 1;
		break;

	case APCI_CONTROL_FIELD_FORMAT_S:
		controlField->octet1 >>= 2;
		controlField->octet1 <<= 2;
		controlField->octet1 |= 1;
		break;

	case APCI_CONTROL_FIELD_FORMAT_U:
		controlField->octet1 >>= 2;
		controlField->octet1 <<= 2;
		controlField->octet1 |= 3;
		break;
	}
}

unsigned short GetSendSequenceNumber(struct APCIControlField* controlField) {
	return *(unsigned short*)controlField >> 1;
}

void SetSendSequenceNumber(unsigned short sendSequenceNumber, struct APCIControlField* controlField) {
	*(unsigned short*)controlField = sendSequenceNumber << 1;
}

unsigned short GetReceiveSequenceNumber(struct APCIControlField* controlField) {
	return *((unsigned short*)controlField + 1) >> 1;
}

void SetReceiveSequenceNumber(unsigned short receiveSequenceNumber, struct APCIControlField* controlField) {
	*((unsigned short*)controlField + 1) = receiveSequenceNumber << 1;
}

unsigned int GetAPCIControlInformation(struct APCIControlField* controlField) {
	switch (controlField->octet1) {
	case 0x07:
		return APCI_CONTROL_INFORMATION_STARTDT_ACT;

	case 0xb:
		return APCI_CONTROL_INFORMATION_STARTDT_CON;

	case 0x13:
		return APCI_CONTROL_INFORMATION_STOPDT_ACT;

	case 0x23:
		return APCI_CONTROL_INFORMATION_STOPDT_CON;

	case 0x43:
		return APCI_CONTROL_INFORMATION_TESTFR_ACT;
	}

	return APCI_CONTROL_INFORMATION_TESTFR_CON;
}

void SetAPCIControlInformation(unsigned int controlInformation, struct APCIControlField* controlField) {
	switch (controlInformation) {
	case APCI_CONTROL_INFORMATION_STARTDT_ACT:
		controlField->octet1 = 0x07;
		break;

	case APCI_CONTROL_INFORMATION_STARTDT_CON:
		controlField->octet1 = 0xb;
		break;

	case APCI_CONTROL_INFORMATION_STOPDT_ACT:
		controlField->octet1 = 0x13;
		break;

	case APCI_CONTROL_INFORMATION_STOPDT_CON:
		controlField->octet1 = 0x23;
		break;

	case APCI_CONTROL_INFORMATION_TESTFR_ACT:
		controlField->octet1 = 0x43;
		break;

	case APCI_CONTROL_INFORMATION_TESTFR_CON:
		controlField->octet1 = 0x83;
		break;
	}
}