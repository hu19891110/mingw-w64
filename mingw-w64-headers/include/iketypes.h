/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */
#ifndef _INC_IKETYPES
#define _INC_IKETYPES
#include <fwptypes.h>

#if (_WIN32_WINNT >= 0x0600)

#ifdef __cplusplus
extern "C" {
#endif

typedef enum IKEEXT_EM_SA_STATE_ {
  IKEEXT_EM_SA_STATE_NONE,
  IKEEXT_EM_SA_STATE_SENT_ATTS,
  IKEEXT_EM_SA_STATE_SSPI_SENT,
  IKEEXT_EM_SA_STATE_AUTH_COMPLETE,
  IKEEXT_EM_SA_STATE_FINAL,
  IKEEXT_EM_SA_STATE_COMPLETE,
  IKEEXT_EM_SA_STATE_MAX 
} IKEEXT_EM_SA_STATE;

typedef enum IKEEXT_SA_ROLE_ {
  IKEEXT_SA_ROLE_INITIATOR,
  IKEEXT_SA_ROLE_RESPONDER,
  IKEEXT_SA_ROLE_MAX 
} IKEEXT_SA_ROLE;

typedef enum IKEEXT_AUTHENTICATION_METHOD_TYPE_ {
  IKEEXT_PRESHARED_KEY,
  IKEEXT_CERTIFICATE,
  IKEEXT_KERBEROS,
  IKEEXT_ANONYMOUS,
  IKEEXT_SSL,
  IKEEXT_NTLM_V2,
  IKEEXT_IPV6_CGA,
  IKEEXT_CERTIFICATE_ECDSA_P256,
  IKEEXT_CERTIFICATE_ECDSA_P384,
  IKEEXT_SSL_ECDSA_P256,
  IKEEXT_SSL_ECDSA_P384,
  IKEEXT_EAP,
  IKEEXT_AUTHENTICATION_METHOD_TYPE_MAX 
} IKEEXT_AUTHENTICATION_METHOD_TYPE;

typedef enum IKEEXT_KEY_MODULE_TYPE_ {
  IKEEXT_KEY_MODULE_IKE,
  IKEEXT_KEY_MODULE_AUTHIP,
  IKEEXT_KEY_MODULE_IKEV2,
  IKEEXT_KEY_MODULE_MAX 
} IKEEXT_KEY_MODULE_TYPE;

typedef enum IKEEXT_MM_SA_STATE_ {
  IKEEXT_MM_SA_STATE_NONE,
  IKEEXT_MM_SA_STATE_SA_SENT,
  IKEEXT_MM_SA_STATE_SSPI_SENT,
  IKEEXT_MM_SA_STATE_FINAL,
  IKEEXT_MM_SA_STATE_FINAL_SENT,
  IKEEXT_MM_SA_STATE_COMPLETE,
  IKEEXT_MM_SA_STATE_MAX 
} IKEEXT_MM_SA_STATE;

typedef enum IKEEXT_QM_SA_STATE_ {
  IKEEXT_QM_SA_STATE_NONE,
  IKEEXT_QM_SA_STATE_INITIAL,
  IKEEXT_QM_SA_STATE_FINAL,
  IKEEXT_QM_SA_STATE_COMPLETE,
  IKEEXT_QM_SA_STATE_MAX 
} IKEEXT_QM_SA_STATE;

typedef enum IKEEXT_AUTHENTICATION_IMPERSONATION_TYPE_ {
  IKEEXT_IMPERSONATION_NONE,
  IKEEXT_IMPERSONATION_SOCKET_PRINCIPAL,
  IKEEXT_IMPERSONATION_MAX 
} IKEEXT_AUTHENTICATION_IMPERSONATION_TYPE;

typedef enum IKEEXT_CERT_CONFIG_TYPE_ {
  IKEEXT_CERT_CONFIG_EXPLICIT_TRUST_LIST,
  IKEEXT_CERT_CONFIG_ENTERPRISE_STORE,
  IKEEXT_CERT_CONFIG_TRUSTED_ROOT_STORE,
  IKEEXT_CERT_CONFIG_UNSPECIFIED,
  IKEEXT_CERT_CONFIG_TYPE_MAX 
} IKEEXT_CERT_CONFIG_TYPE;

typedef enum IKEEXT_CIPHER_TYPE_ {
  IKEEXT_CIPHER_DES,
  IKEEXT_CIPHER_3DES,
  IKEEXT_CIPHER_AES_128,
  IKEEXT_CIPHER_AES_192,
  IKEEXT_CIPHER_AES_256,
  IKEEXT_CIPHER_TYPE_MAX 
} IKEEXT_CIPHER_TYPE;

typedef enum IKEEXT_INTEGRITY_TYPE_ {
  IKEEXT_INTEGRITY_MD5,
  IKEEXT_INTEGRITY_SHA1,
  IKEEXT_INTEGRITY_SHA_256,
  IKEEXT_INTEGRITY_SHA_384,
  IKEEXT_INTEGRITY_TYPE_MAX 
} IKEEXT_INTEGRITY_TYPE;

typedef enum IKEEXT_DH_GROUP_ {
  IKEEXT_DH_GROUP_NONE,
  IKEEXT_DH_GROUP_1,
  IKEEXT_DH_GROUP_2,
  IKEEXT_DH_GROUP_2048,
  IKEEXT_DH_ECP_256,
  IKEEXT_DH_ECP_384,
  IKEEXT_DH_GROUP_MAX 
} IKEEXT_DH_GROUP;

typedef struct IKEEXT_CERT_ROOT_CONFIG0_ {
  FWP_BYTE_BLOB certData;
  UINT32        flags;
} IKEEXT_CERT_ROOT_CONFIG0;

typedef struct IKEEXT_EM_POLICY0_ {
  UINT32                                   numAuthenticationMethods;
  IKEEXT_AUTHENTICATION_METHOD0            *authenticationMethods;
  IKEEXT_AUTHENTICATION_IMPERSONATION_TYPE initiatorImpersonationType;
} IKEEXT_EM_POLICY0;

typedef struct IKEEXT_KERBEROS_AUTHENTICATION0_ {
  UINT32 flags;
} IKEEXT_KERBEROS_AUTHENTICATION0;

typedef struct IKEEXT_NTLM_V2_AUTHENTICATION0_ {
  UINT32 flags;
} IKEEXT_NTLM_V2_AUTHENTICATION0;

typedef struct IKEEXT_IPV6_CGA_AUTHENTICATION0_ {
  wchar_t          *keyContainerName;
  wchar_t          *cspName;
  UINT32           cspType;
  FWP_BYTE_ARRAY16 cgaModifier;
  BYTE             cgaCollisionCount;
} IKEEXT_IPV6_CGA_AUTHENTICATION0;

typedef struct IKEEXT_PRESHARED_KEY_AUTHENTICATION0__ {
  FWP_BYTE_BLOB presharedKey;
} IKEEXT_PRESHARED_KEY_AUTHENTICATION0;

typedef struct IKEEXT_AUTHENTICATION_METHOD0_ {
  IKEEXT_AUTHENTICATION_METHOD_TYPE authenticationMethodType;
  __MINGW_EXTENSION union {
    IKEEXT_PRESHARED_KEY_AUTHENTICATION0 presharedKeyAuthentication;
    IKEEXT_CERTIFICATE_AUTHENTICATION0   certificateAuthentication;
    IKEEXT_KERBEROS_AUTHENTICATION0      kerberosAuthentication;
    IKEEXT_NTLM_V2_AUTHENTICATION0       ntlmV2Authentication;
    IKEEXT_CERTIFICATE_AUTHENTICATION0   sslAuthentication;
    IKEEXT_IPV6_CGA_AUTHENTICATION0      cgaAuthentication;
    ;      // case(IKEEXT_ANONYMOUS)
  };
} IKEEXT_AUTHENTICATION_METHOD0;

typedef struct IKEEXT_CERTIFICATE_AUTHENTICATION0_ {
  IKEEXT_CERT_CONFIG_TYPE inboundConfigType;
  __MINGW_EXTENSION union {
    __MINGW_EXTENSION struct {
      UINT32                   inboundRootArraySize;
      IKEEXT_CERT_ROOT_CONFIG0 *inboundRootArray;
    };
    IKEEXT_CERT_ROOT_CONFIG0 *inboundEnterpriseStoreConfig;
    IKEEXT_CERT_ROOT_CONFIG0 *inboundTrustedRootStoreConfig;
  };
  IKEEXT_CERT_CONFIG_TYPE outboundConfigType;
  __MINGW_EXTENSION union {
    __MINGW_EXTENSION struct {
      UINT32                   outboundRootArraySize;
      IKEEXT_CERT_ROOT_CONFIG0 *outboundRootArray;
    };
    IKEEXT_CERT_ROOT_CONFIG0 *outboundEnterpriseStoreConfig;
    IKEEXT_CERT_ROOT_CONFIG0 *outboundTrustedRootStoreConfig;
  };
  UINT32                  flags;
} IKEEXT_CERTIFICATE_AUTHENTICATION0;

typedef struct IKEEXT_POLICY0_ {
  UINT32                                   softExpirationTime;
  UINT32                                   numAuthenticationMethods;
  IKEEXT_AUTHENTICATION_METHOD0            *authenticationMethods;
  IKEEXT_AUTHENTICATION_IMPERSONATION_TYPE initiatorImpersonationType;
  UINT32                                   numIkeProposals;
  IKEEXT_PROPOSAL0                         *ikeProposals;
  UINT32                                   flags;
  UINT32                                   maxDynamicFilters;
} IKEEXT_POLICY0;

typedef struct IKEEXT_INTEGRITY_ALGORITHM0_ {
  IKEEXT_INTEGRITY_TYPE algoIdentifier;
} IKEEXT_INTEGRITY_ALGORITHM0;

typedef struct IKEEXT_CIPHER_ALGORITHM0_ {
  IKEEXT_CIPHER_TYPE algoIdentifier;
  UINT32             keyLen;
  UINT32             rounds;
} IKEEXT_CIPHER_ALGORITHM0;

typedef struct IKEEXT_PROPOSAL0_ {
  IKEEXT_CIPHER_ALGORITHM0    cipherAlgorithm;
  IKEEXT_INTEGRITY_ALGORITHM0 integrityAlgorithm;
  UINT32                      maxLifetimeSeconds;
  IKEEXT_DH_GROUP             dhGroup;
  UINT32                      quickModeLimit;
} IKEEXT_PROPOSAL0;

typedef struct IKEEXT_CERTIFICATE_CREDENTIAL0_ {
  FWP_BYTE_BLOB subjectName;
  FWP_BYTE_BLOB certHash;
  UINT32        flags;
} IKEEXT_CERTIFICATE_CREDENTIAL0;

typedef struct IKEEXT_IP_VERSION_SPECIFIC_COMMON_STATISTICS0_ {
  UINT32 totalSocketReceiveFailures;
  UINT32 totalSocketSendFailures;
} IKEEXT_IP_VERSION_SPECIFIC_COMMON_STATISTICS0;

typedef struct IKEEXT_COMMON_STATISTICS0_ {
  IKEEXT_IP_VERSION_SPECIFIC_COMMON_STATISTICS0 v4Statistics;
  IKEEXT_IP_VERSION_SPECIFIC_COMMON_STATISTICS0 v6Statistics;
  UINT32                                        totalPacketsReceived;
  UINT32                                        totalInvalidPacketsReceived;
  UINT32                                        currentQueuedWorkitems;
} IKEEXT_COMMON_STATISTICS0;

typedef UINT64 IKEEXT_COOKIE;

typedef struct IKEEXT_COOKIE_PAIR0_ {
  IKEEXT_COOKIE initiator;
  IKEEXT_COOKIE responder;
} IKEEXT_COOKIE_PAIR0;

typedef struct IKEEXT_CREDENTIAL0_ {
  IKEEXT_AUTHENTICATION_METHOD_TYPE        authenticationMethodType;
  IKEEXT_AUTHENTICATION_IMPERSONATION_TYPE impersonationType;
  __MINGW_EXTENSION union {
    IKEEXT_PRESHARED_KEY_AUTHENTICATION0 *presharedKey;
    IKEEXT_CERTIFICATE_CREDENTIAL0       *certificate;
    IKEEXT_NAME_CREDENTIAL0              *name;
    ;      // case(IKEEXT_ANONYMOUS)
  };
} IKEEXT_CREDENTIAL0;

typedef struct IKEEXT_CREDENTIAL_PAIR0_ {
  IKEEXT_CREDENTIAL0 localCredentials;
  IKEEXT_CREDENTIAL0 peerCredentials;
} IKEEXT_CREDENTIAL_PAIR0;

typedef struct IKEEXT_CREDENTIALS0_ {
  UINT32                  numCredentials;
  IKEEXT_CREDENTIAL_PAIR0 *credentials;
} IKEEXT_CREDENTIALS0;

typedef struct IKEEXT_IP_VERSION_SPECIFIC_KEYMODULE_STATISTICS0_ {
  UINT32 currentActiveMainModes;
  UINT32 totalMainModesStarted;
  UINT32 totalSuccessfulMainModes;
  UINT32 totalFailedMainModes;
  UINT32 totalResponderMainModes;
  UINT32 currentNewResponderMainModes;
  UINT32 currentActiveQuickModes;
  UINT32 totalQuickModesStarted;
  UINT32 totalSuccessfulQuickModes;
  UINT32 totalFailedQuickModes;
  UINT32 totalAcquires;
  UINT32 totalReinitAcquires;
  UINT32 currentActiveExtendedModes;
  UINT32 totalExtendedModesStarted;
  UINT32 totalSuccessfulExtendedModes;
  UINT32 totalFailedExtendedModes;
  UINT32 totalImpersonationExtendedModes;
  UINT32 totalImpersonationMainModes;
} IKEEXT_IP_VERSION_SPECIFIC_KEYMODULE_STATISTICS0;

#define IKEEXT_ERROR_CODE_COUNT (ERROR_IPSEC_IKE_NEG_STATUS_END - ERROR_IPSEC_IKE_NEG_STATUS_BEGIN) /* Should be 84 */

typedef struct IKEEXT_KEYMODULE_STATISTICS0_ {
  IKEEXT_IP_VERSION_SPECIFIC_KEYMODULE_STATISTICS0 v4Statistics;
  IKEEXT_IP_VERSION_SPECIFIC_KEYMODULE_STATISTICS0 v6Statistics;
  UINT32                                           errorFrequencyTable[IKEEXT_ERROR_CODE_COUNT];
  UINT32                                           mainModeNegotiationTime;
  UINT32                                           quickModeNegotiationTime;
  UINT32                                           extendedModeNegotiationTime;
} IKEEXT_KEYMODULE_STATISTICS0;

typedef struct IKEEXT_NAME_CREDENTIAL0_ {
  wchar_t *principalName;
} IKEEXT_NAME_CREDENTIAL0;

typedef struct IKEEXT_SA_DETAILS0_ {
  UINT64                 saId;
  IKEEXT_KEY_MODULE_TYPE keyModuleType;
  FWP_IP_VERSION         ipVersion;
  __MINGW_EXTENSION union {
    IPSEC_V4_UDP_ENCAPSULATION0 *v4UdpEncapsulation;
    ;      // case(FWP_IP_VERSION_V6)
  };
  IKEEXT_TRAFFIC0        ikeTraffic;
  IKEEXT_PROPOSAL0       ikeProposal;
  IKEEXT_COOKIE_PAIR0    cookiePair;
  IKEEXT_CREDENTIALS0    ikeCredentials;
  GUID                   ikePolicyKey;
  UINT64                 virtualIfTunnelId;
} IKEEXT_SA_DETAILS0;

typedef struct IKEEXT_SA_ENUM_TEMPLATE0_ {
  FWP_CONDITION_VALUE0 localSubNet;
  FWP_CONDITION_VALUE0 remoteSubNet;
  FWP_BYTE_BLOB        localMainModeCertHash;
} IKEEXT_SA_ENUM_TEMPLATE0;

typedef struct IKEEXT_STATISTICS0_ {
  IKEEXT_KEYMODULE_STATISTICS0 ikeStatistics;
  IKEEXT_KEYMODULE_STATISTICS0 authipStatistics;
  IKEEXT_COMMON_STATISTICS0    commonStatistics;
} IKEEXT_STATISTICS0;

typedef struct IKEEXT_TRAFFIC0_ {
  FWP_IP_VERSION ipVersion;
  __MINGW_EXTENSION union {
    UINT32 localV4Address;
    UINT8  localV6Address[16];
  };
  __MINGW_EXTENSION union {
    UINT32 remoteV4Address;
    UINT8  remoteV6Address[16];
  };
  UINT64         authIpFilterId;
} IKEEXT_TRAFFIC0;

#ifdef __cplusplus
}
#endif
#endif /*(_WIN32_WINNT >= 0x0600)*/
#endif /*_INC_IKETYPES*/