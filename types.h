#pragma once

#define M_SP_NA_1 1
#define M_SP_TA_1 2

#define M_DP_NA_1 3
#define M_DP_TA_1 4

#define M_ST_NA_1 5
#define M_ST_TA_1 6

#define M_BO_NA_1 7
#define M_BO_TA_1 8

#define M_ME_NA_1 9
#define M_ME_TA_1 10

#define M_ME_NB_1 11
#define M_ME_TB_1 12

#define M_ME_NC_1 13
#define M_ME_TC_1 14

#define M_IT_NA_1 15
#define M_IT_TA_1 16

#define M_EP_TA_1 17
#define M_EP_TB_1 18
#define M_EP_TC_1 19
#define M_PS_NA_1 20
#define M_ME_ND_1 21

#define M_SP_TB_1 30
#define M_DP_SP_1 31

#define M_ST_TB_1 32
#define M_BO_TB_1 33

#define M_ME_TD_1 34
#define M_ME_TE_1 35
#define M_ME_TF_1 36

#define M_IT_TB_1 37
#define M_EP_TD_1 38
#define M_EP_TE_1 39
#define M_EP_TF_1 40

#define C_SC_NA_1 45
#define C_DC_NA_1 46
#define C_RC_NA_1 47

#define C_SE_NA_1 48
#define C_SE_NB_1 49
#define C_SE_NC_1 50
#define C_BO_NA_1 51

#define M_EL_NA_1 70

#define C_IC_NA_1 100
#define C_CI_NA_1 101
#define C_RD_NA_1 102
#define C_CS_NA_1 103
#define C_TS_NA_1 104
#define C_RP_NA_1 105
#define C_CD_NA_1 106

#define P_ME_NA_1 110
#define P_ME_NB_1 111
#define P_ME_NC_1 112
#define P_AC_NA_1 113

#define F_FR_NA_1 120
#define F_SR_NA_1 121
#define F_SC_NA_1 122
#define F_LS_NA_1 123
#define F_AF_NA_1 124
#define F_SG_NA_1 125
#define F_DR_TA_1 126

struct APCIControlField {
	unsigned char octet1;
	unsigned char octet2;
	unsigned char octet3;
	unsigned char octet4;
};

struct APCI {
	unsigned char start;
	unsigned char lengthOfAPDU;
	struct APCIControlField controlField;
};

struct VariableStructureQualifier {
	unsigned char number : 7;
	unsigned char SQ : 1;
};

struct CauseOfTransmission {
	unsigned char cause : 6;
	unsigned char PN : 1;
	unsigned char test : 1;
	unsigned char originatorAddress;
};

struct CommonAddressOfASDU {
	unsigned char octet1;
	unsigned char octet2;
};

struct DataUnitIdentifier {
	unsigned char typeIdentification;
	struct VariableStructureQualifier variableStructureQualifier;

	struct CauseOfTransmission causeOfTransmission;
	struct CommonAddressOfASDU commonAddressOfASDU;
};

struct InformationObjectIdentifier {
	unsigned char informationObjectAddressOctet1;
	unsigned char informationObjectAddressOctet2;
	unsigned char informationObjectAddressOctet3;
};

struct QDS {
	unsigned char OV : 1;
	unsigned char RES : 3;
	unsigned char BL : 1;
	unsigned char SB : 1;
	unsigned char NT : 1;
	unsigned char IV : 1;
};

struct SIQ {
	unsigned char SPI : 1;
	unsigned char RES : 3;
	unsigned char BL : 1;
	unsigned char SB : 1;
	unsigned char NT : 1;
	unsigned char IV : 1;
};

struct DIQ {
	unsigned char DPI : 2;
	unsigned char RES : 2;
	unsigned char BL : 1;
	unsigned char SB : 1;
	unsigned char NT : 1;
	unsigned char IV : 1;
};

struct VTI {
	char value : 7;
	char transient : 1;
};

struct BCR {
	char counterReadingOctet1;
	char counterReadingOctet2;
	char counterReadingOctet3;
	char counterReadingOctet4;

	unsigned char SQ : 5;
	unsigned char CY : 1;
	unsigned char CA : 1;
	unsigned char IV : 1;
};

struct SCO {
	unsigned char SCS : 1;
	unsigned char RES : 1;
	unsigned char QU : 5;
	unsigned char SE : 1;
};

struct DCO {
	unsigned char DCS : 2;
	unsigned char QU : 5;
	unsigned char SE : 1;
};

struct RCO {
	unsigned char RCS : 2;
	unsigned char QU : 5;
	unsigned char SE : 1;
};

struct CP56Time2a {
	unsigned char millisecondsOctet1;
	unsigned char millisecondsOctet2;

	unsigned char minutes : 6;
	unsigned char RES1 : 1;
	unsigned char IV : 1;
	unsigned char hours : 5;
	unsigned char RES2 : 2;
	unsigned char SU : 1;
	unsigned char dayOfMonth : 5;
	unsigned char dayOfWeek : 3;
	unsigned char months : 4;
	unsigned char RES3 : 4;
	unsigned char years : 7;
	unsigned char RES4 : 1;
};

struct CP24Time2a {
	unsigned char millisecondsOctet1;
	unsigned char millisecondsOctet2;

	unsigned char minutes : 6;
	unsigned char RES1 : 1;
	unsigned char IV : 1;
};

struct InformationObject {
	struct InformationObjectIdentifier informationObjectIdentifier;
	unsigned char* informationElementBuffer;
};

struct APSU {
	struct DataUnitIdentifier dataUnitIdentifier;
	struct InformationObject* informationObjects;
};

struct APDU {
	struct APCI apci;
	struct APSU* apsu;
};

struct APDU STARTDT_ACT_APDU = { 0x68, 0x04, 0x07, 0x0, 0x0, 0x0, 0 };
struct APDU STARTDT_CON_APDU = { 0x68, 0x04, 0xb, 0x0, 0x0, 0x0, 0 };

struct APDU STOPDT_ACT_APDU = { 0x68, 0x04, 0x13, 0x0, 0x0, 0x0, 0 };
struct APDU STOPDT_CON_APDU = { 0x68, 0x04, 0x23, 0x0, 0x0, 0x0, 0 };

struct APDU TESTFR_ACT_APDU = { 0x68, 0x04, 0x43, 0x0, 0x0, 0x0, 0 };
struct APDU TESTFR_CON_APDU = { 0x68, 0x04, 0x83, 0x0, 0x0, 0x0, 0 };