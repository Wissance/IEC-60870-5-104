#ifndef TYPES_H
#define TYPES_H

// Process information in monitor direction:
#define M_SP_NA_1 1 // Single-point information
#define M_SP_TA_1 2 // Single-point information with time tag

#define M_DP_NA_1 3 // Double-point information
#define M_DP_TA_1 4 // Double-point information with time tag

#define M_ST_NA_1 5 // Step position information
#define M_ST_TA_1 6 // Step position information with time tag

#define M_BO_NA_1 7 // Bitstring of 32 bit
#define M_BO_TA_1 8 // Bitstring of 32 bit with time tag

#define M_ME_NA_1 9 // Measured value, normalized value
#define M_ME_TA_1 10 // Measured value, normalized value with time tag

#define M_ME_NB_1 11 // Measured value, scaled value
#define M_ME_TB_1 12 // Measured value, scaled value with time tag

#define M_ME_NC_1 13 // Measured value, short floating point number
#define M_ME_TC_1 14 // Measured value, short floating point number with time tag

#define M_IT_NA_1 15 // Integrated totals
#define M_IT_TA_1 16 // Integrated totals with time tag

#define M_EP_TA_1 17 // Event of protection equipment with time tag
#define M_EP_TB_1 18 // Packed start events of protection equipment with time tag
#define M_EP_TC_1 19 // Packed output circuit information of protection equipment with time tag
#define M_PS_NA_1 20 // Point information with status change detection
#define M_ME_ND_1 21 // Measured value, normalized value without quality descriptor

#define M_SP_TB_1 30 // Single-point information with time tag CP56Time2a
#define M_DP_SP_1 31 // Double-point information with time tag CP56Time2a

#define M_ST_TB_1 32 // Step position information with time tag CP56Time2a
#define M_BO_TB_1 33 // Bitstring of 32 bits with time tag CP56Time2a

#define M_ME_TD_1 34 // Measured value, normalized value with time tag CP56Time2a
#define M_ME_TE_1 35 // Measured value, scaled value with time tag CP56Time2a
#define M_ME_TF_1 36 // Measured value, short floating point number with time tag CP56Time2a

#define M_IT_TB_1 37 // Integrated totals with time tag CP56Time2a
#define M_EP_TD_1 38 // Event of protection equipment with time tag CP56Time2a
#define M_EP_TE_1 39 // Packed start events of protection equipment with time tag CP56Time2a
#define M_EP_TF_1 40 // Packed output circuit information of protection equipment with time tag CP56Time2a

// Process information in control direction:
#define C_SC_NA_1 45 // Single command
#define C_DC_NA_1 46 // Double command
#define C_RC_NA_1 47 // Regulating step command

#define C_SE_NA_1 48 // Set point command, normalized value
#define C_SE_NB_1 49 // Set point command, scaled value
#define C_SE_NC_1 50 // Set point command, short floating point number
#define C_BO_NA_1 51 // Bitstring of 32 bits

// ASDUs marked (CON) in control direction are confirmed application services and may be mirrored in
// monitor direction with different causes acknowledgements(verifications).

// System information in monitor direction:
#define M_EL_NA_1 70 // End of initialization

// System information in control direction:
#define C_IC_NA_1 100 // Interrogation command
#define C_CI_NA_1 101 // Counter interrogation command
#define C_RD_NA_1 102 // Read command
#define C_CS_NA_1 103 // Clock synchronization command
#define C_TS_NA_1 104 // Test command
#define C_RP_NA_1 105 // Reset process command
#define C_CD_NA_1 106 // Delay acquisition command

// Parameter in control direction:
#define P_ME_NA_1 110 // Parameter of measured value, normalized value
#define P_ME_NB_1 111 // Parameter of measured value, scaled value
#define P_ME_NC_1 112 // Parameter of measured value, short floating point number
#define P_AC_NA_1 113 // Parameter activation

// File transfer:
#define F_FR_NA_1 120 // File ready
#define F_SR_NA_1 121 // Section ready
#define F_SC_NA_1 122 // Call directory, select file, call file, call section
#define F_LS_NA_1 123 // Last section, last segment
#define F_AF_NA_1 124 // Ack file, ack section
#define F_SG_NA_1 125 // Segment
#define F_DR_TA_1 126 // Directory

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

// Quality descriptor (separate octet)
struct QDS {
	unsigned char OV : 1;
	unsigned char RES : 3;
	unsigned char BL : 1;
	unsigned char SB : 1;
	unsigned char NT : 1;
	unsigned char IV : 1;
};

// Single-point information (IEV 371-02-07) with quality descriptor
struct SIQ {
	unsigned char SPI : 1;
	unsigned char RES : 3;
	unsigned char BL : 1;
	unsigned char SB : 1;
	unsigned char NT : 1;
	unsigned char IV : 1;
};

// Double-point information (IEV 371-02-08) with quality descriptor
struct DIQ {
	unsigned char DPI : 2;
	unsigned char RES : 2;
	unsigned char BL : 1;
	unsigned char SB : 1;
	unsigned char NT : 1;
	unsigned char IV : 1;
};

// Value with transient state indication
struct VTI {
	char value : 7;
	char transient : 1;
};

// Binary counter reading
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

// Single command (IEV 371-03-02)
struct SCO {
	unsigned char SCS : 1;
	unsigned char RES : 1;
	unsigned char QU : 5;
	unsigned char SE : 1;
};

// Double command (IEV 371-03-03)
struct DCO {
	unsigned char DCS : 2;
	unsigned char QU : 5;
	unsigned char SE : 1;
};

// Regulating step command (IEV 371-03-13)
struct RCO {
	unsigned char RCS : 2;
	unsigned char QU : 5;
	unsigned char SE : 1;
};

// Seven octet binary time
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

// Three octet binary time
struct CP24Time2a {
	unsigned char millisecondsOctet1;
	unsigned char millisecondsOctet2;

	unsigned char minutes : 6;
	unsigned char RES1 : 1;
	unsigned char IV : 1;
};

// Scaled value
typedef short SVA;

// Normalized value
typedef unsigned short NVA;

// Short floating-point number
typedef unsigned short float16;

// Binary state information (IEV 371-02-03) 32 bit
typedef unsigned int BSI;

// Fixed test bit pattern, two octets
typedef unsigned short FBP;

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

#endif