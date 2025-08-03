/*
 ============================================================================
 Name        : error_codes.h
 Author      : hev <r@hev.cc>
 Copyright   : Copyright (c) 2017 - 2024 hev
 Description : Extended error codes
 ============================================================================
 */

#ifndef __ERROR_CODES_H__
#define __ERROR_CODES_H__

/* Success */
#define HEV_ERROR_SUCCESS                   0

/* General errors */
#define HEV_ERROR_INVALID_PARAMETER        -1
#define HEV_ERROR_OUT_OF_MEMORY            -2
#define HEV_ERROR_OPERATION_FAILED         -3
#define HEV_ERROR_NOT_SUPPORTED            -4
#define HEV_ERROR_TIMEOUT                  -5
#define HEV_ERROR_INTERRUPTED              -6

/* Configuration errors */
#define HEV_ERROR_CONFIG_INVALID_FILE      -100
#define HEV_ERROR_CONFIG_PARSE_ERROR       -101
#define HEV_ERROR_CONFIG_MISSING_REQUIRED  -102
#define HEV_ERROR_CONFIG_INVALID_VALUE     -103
#define HEV_ERROR_CONFIG_INVALID_PORT      -104
#define HEV_ERROR_CONFIG_INVALID_IP        -105
#define HEV_ERROR_CONFIG_INVALID_PATH      -106

/* Network errors */
#define HEV_ERROR_NETWORK_SOCKET_FAILED    -200
#define HEV_ERROR_NETWORK_BIND_FAILED      -201
#define HEV_ERROR_NETWORK_CONNECT_FAILED   -202
#define HEV_ERROR_NETWORK_ACCEPT_FAILED    -203
#define HEV_ERROR_NETWORK_SEND_FAILED      -204
#define HEV_ERROR_NETWORK_RECV_FAILED      -205
#define HEV_ERROR_NETWORK_ADDRESS_IN_USE   -206
#define HEV_ERROR_NETWORK_CONNECTION_REFUSED -207
#define HEV_ERROR_NETWORK_HOST_UNREACHABLE -208

/* Authentication errors */
#define HEV_ERROR_AUTH_INVALID_CREDENTIALS -300
#define HEV_ERROR_AUTH_FILE_NOT_FOUND      -301
#define HEV_ERROR_AUTH_FILE_READ_ERROR     -302
#define HEV_ERROR_AUTH_FILE_FORMAT_ERROR   -303
#define HEV_ERROR_AUTH_USER_NOT_FOUND      -304

/* Protocol errors */
#define HEV_ERROR_PROTOCOL_INVALID_VERSION -400
#define HEV_ERROR_PROTOCOL_INVALID_COMMAND -401
#define HEV_ERROR_PROTOCOL_INVALID_ADDRESS -402
#define HEV_ERROR_PROTOCOL_UNSUPPORTED_METHOD -403
#define HEV_ERROR_PROTOCOL_MALFORMED_PACKET -404

/* File system errors */
#define HEV_ERROR_FILE_NOT_FOUND           -500
#define HEV_ERROR_FILE_ACCESS_DENIED       -501
#define HEV_ERROR_FILE_READ_ERROR          -502
#define HEV_ERROR_FILE_WRITE_ERROR         -503
#define HEV_ERROR_FILE_DELETE_ERROR        -504
#define HEV_ERROR_FILE_ALREADY_EXISTS      -505

/* String operation errors */
#define HEV_ERROR_STRING_NULL_POINTER      -600
#define HEV_ERROR_STRING_BUFFER_OVERFLOW   -601
#define HEV_ERROR_STRING_INVALID_FORMAT    -602
#define HEV_ERROR_STRING_TRUNCATED         -603

/* System errors */
#define HEV_ERROR_SYSTEM_RESOURCE_EXHAUSTED -700
#define HEV_ERROR_SYSTEM_PERMISSION_DENIED  -701
#define HEV_ERROR_SYSTEM_NOT_IMPLEMENTED    -702

/**
 * @brief Get error message for error code
 * @param error_code Error code
 * @return Error message string
 */
const char *hev_error_get_message(int error_code);

/**
 * @brief Check if error code indicates success
 * @param error_code Error code to check
 * @return 1 if success, 0 if error
 */
int hev_error_is_success(int error_code);

/**
 * @brief Check if error code indicates a configuration error
 * @param error_code Error code to check
 * @return 1 if config error, 0 otherwise
 */
int hev_error_is_config_error(int error_code);

/**
 * @brief Check if error code indicates a network error
 * @param error_code Error code to check
 * @return 1 if network error, 0 otherwise
 */
int hev_error_is_network_error(int error_code);

#endif /* __ERROR_CODES_H__ */ 