#include "functions.h"
#include "types.h"

unsigned int getAPCIControlFieldFormat(struct APCIControlField* controlField)
{
	if (!(controlField->octet1 & 1))
		return APCI_CONTROL_FIELD_FORMAT_I;

	if (!(controlField->octet1 & 2))
		return APCI_CONTROL_FIELD_FORMAT_S;

	return APCI_CONTROL_FIELD_FORMAT_U;
}

void setAPCIControlFieldFormat(unsigned int controlFieldFormat, struct APCIControlField* controlField)
{
	switch (controlFieldFormat)
  {
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

unsigned short getSendSequenceNumber(struct APCIControlField* controlField)
{
	return *(unsigned short*)controlField >> 1;
}

void setSendSequenceNumber(unsigned short sendSequenceNumber, struct APCIControlField* controlField)
{
	*(unsigned short*)controlField = sendSequenceNumber << 1;
}

unsigned short getReceiveSequenceNumber(struct APCIControlField* controlField)
{
	return *((unsigned short*)controlField + 1) >> 1;
}

void setReceiveSequenceNumber(unsigned short receiveSequenceNumber, struct APCIControlField* controlField)
{
	*((unsigned short*)controlField + 1) = receiveSequenceNumber << 1;
}

unsigned int getAPCIControlInformation(struct APCIControlField* controlField)
{
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

void setAPCIControlInformation(unsigned int controlInformation, struct APCIControlField* controlField)
{
	switch (controlInformation)
  {
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

unsigned int checkSocketForReadability(SOCKET endpoint, long seconds, long microseconds)
{
	struct fd_set fileDescriptorSet;
	FD_ZERO(&fileDescriptorSet);
	FD_SET(endpoint, &fileDescriptorSet);

	struct timeval timeout = { seconds, microseconds };

	int result = select(0, &fileDescriptorSet, 0, 0, &timeout);

	if (result == SOCKET_ERROR)
		return 2;
	else if (result == 0)
		return 0;
	else
		return 1;
}

unsigned int checkSocketForWritability(SOCKET endpoint, long seconds, long microseconds)
{
	struct fd_set fileDescriptorSet;
	FD_ZERO(&fileDescriptorSet);
	FD_SET(endpoint, &fileDescriptorSet);

	struct timeval timeout = { seconds, microseconds };

	int result = select(0, 0, &fileDescriptorSet, 0, &timeout);

	if (result == SOCKET_ERROR)
		return 2;
	else if (result == 0)
		return 0;
	else
		return 1;
}

unsigned int checkSocketForErrors(SOCKET endpoint, long seconds, long microseconds)
{
	struct fd_set fileDescriptorSet;
	FD_ZERO(&fileDescriptorSet);
	FD_SET(endpoint, &fileDescriptorSet);

	struct timeval timeout = { seconds, microseconds };

	int result = select(0, 0, 0, &fileDescriptorSet, &timeout);

	if (result == SOCKET_ERROR)
		return 2;
	else if (result == 0)
		return 0;
	else
		return 1;
}

unsigned int readFromSocket(
	SOCKET endpoint,
	unsigned char* buffer,
	unsigned int numberOfBytesToRead,
	unsigned int* numberOfBytesRead)
{
	*numberOfBytesRead = 0;

	int result = recv(endpoint, (char*)buffer, numberOfBytesToRead, 0);

	if (result == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return 0;

		return 3;
	}
	else if (result == 0)
		return 2;
	else
	{
		*numberOfBytesRead = result;

		return 1;
	}
}

unsigned int writeToSocket(
	SOCKET endpoint,
	const unsigned char* buffer,
	unsigned int numberOfBytesToWrite,
	unsigned int* numberOfBytesWritten)
{
	*numberOfBytesWritten = 0;

	int result = send(endpoint, (const char*)buffer, numberOfBytesToWrite, 0);

	if (result == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
			return 0;

		return 3;
	}
	else if (result == 0)
		return 2;
	else
	{
		*numberOfBytesWritten = result;

		return 1;
	}
}

unsigned int receiveAPDU(SOCKET endpoint, unsigned char* APDUBuffer)
{
	unsigned int totalNumberOfBytesRead = 0;
	unsigned int numberOfBytesRead;
	unsigned int result;

	while (1)
	{
		result = checkSocketForReadability(endpoint, 0, 5000);

		if (result == 0)
			return 0;

		else if (result == 1)
		{
			if (totalNumberOfBytesRead == 0)
			{
				result = readFromSocket(endpoint, &APDUBuffer[totalNumberOfBytesRead], 1, &numberOfBytesRead);

				if (result == 1)
					totalNumberOfBytesRead += numberOfBytesRead;
				else if (result == 2)
					return 2;
				else
					return 3;
			}

			if (totalNumberOfBytesRead == 1)
			{
				result = readFromSocket(endpoint, &APDUBuffer[totalNumberOfBytesRead], 1, &numberOfBytesRead);

				if (result == 0)
					continue;
				else if (result == 1)
					totalNumberOfBytesRead += numberOfBytesRead;
				else if (result == 2)
					return 2;
				else
					return 3;
			}

			if (totalNumberOfBytesRead > 1)
			{
				result = readFromSocket(
					endpoint,
					&APDUBuffer[totalNumberOfBytesRead],
					((unsigned int)APDUBuffer[2] + 2) - totalNumberOfBytesRead,
					&numberOfBytesRead);

				if (result == 0)
					continue;
				else if (result == 1)
					totalNumberOfBytesRead += numberOfBytesRead;
				else if (result == 2)
					return 2;
				else
					return 3;

				if (totalNumberOfBytesRead == (unsigned int)APDUBuffer[2])
					return 1;
			}
		}
		else
			return 3;
	}
}

unsigned int sendAPDU(SOCKET endpoint, const unsigned char* APDUBuffer)
{
	unsigned int totalNumberOfBytesWritten = 0;
	unsigned int numberOfBytesWritten;
	unsigned int result;

	while (1)
	{
		result = checkSocketForWritability(endpoint, 0, 5000);

		if (result == 0)
			return 0;

		else if (result == 1)
		{
			result = writeToSocket(
				endpoint,
				&APDUBuffer[numberOfBytesWritten],
				(unsigned int)APDUBuffer[2] - totalNumberOfBytesWritten,
				&numberOfBytesWritten);

			if (result == 0)
				continue;
			else if (result == 1)
				totalNumberOfBytesWritten += numberOfBytesWritten;
			else if (result == 2)
				return 2;
			else
				return 3;

			if (totalNumberOfBytesWritten == (unsigned int)APDUBuffer[2])
				return 1;
		}
		else
			return 3;
	}
}

bool ConnectToControlledStation(const char* IPAddress, unsigned short port, SOCKET* clientSocket)
{
	SOCKADDR_STORAGE addrStorage;
	sockaddr_in* addrIn = (sockaddr_in*)(&addrStorage);

	const unsigned short addrFamily = AF_INET;
	addrIn->sin_family = addrFamily;
	addrIn->sin_port = htons(port);

	InetPtonA(addrFamily, IPAddress, &addrIn->sin_addr);

	*clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (!connect(*clientSocket, (sockaddr*)addrIn, sizeof(sockaddr)))
		return true;

	return false;
}