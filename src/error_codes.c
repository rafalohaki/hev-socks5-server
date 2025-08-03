/*
 ============================================================================
 Name        : error_codes.c
 Author      : hev <r@hev.cc>
 Copyright   : Copyright (c) 2017 - 2024 hev
 Description : Extended error codes implementation
 ============================================================================
 */

#include "error_codes.h"

const char *
hev_error_get_message(int error_code)
{
    switch (error_code) {
        case HEV_ERROR_SUCCESS:
            return "Operation completed successfully";
            
        case HEV_ERROR_INVALID_PARAMETER:
            return "Invalid parameter provided";
        case HEV_ERROR_OUT_OF_MEMORY:
            return "Out of memory";
        case HEV_ERROR_OPERATION_FAILED:
            return "Operation failed";
        case HEV_ERROR_NOT_SUPPORTED:
            return "Operation not supported";
        case HEV_ERROR_TIMEOUT:
            return "Operation timed out";
        case HEV_ERROR_INTERRUPTED:
            return "Operation was interrupted";
            
        case HEV_ERROR_CONFIG_INVALID_FILE:
            return "Invalid configuration file";
        case HEV_ERROR_CONFIG_PARSE_ERROR:
            return "Configuration parse error";
        case HEV_ERROR_CONFIG_MISSING_REQUIRED:
            return "Missing required configuration parameter";
        case HEV_ERROR_CONFIG_INVALID_VALUE:
            return "Invalid configuration value";
        case HEV_ERROR_CONFIG_INVALID_PORT:
            return "Invalid port number";
        case HEV_ERROR_CONFIG_INVALID_IP:
            return "Invalid IP address";
        case HEV_ERROR_CONFIG_INVALID_PATH:
            return "Invalid file path";
            
        case HEV_ERROR_NETWORK_SOCKET_FAILED:
            return "Socket creation failed";
        case HEV_ERROR_NETWORK_BIND_FAILED:
            return "Socket bind failed";
        case HEV_ERROR_NETWORK_CONNECT_FAILED:
            return "Connection failed";
        case HEV_ERROR_NETWORK_ACCEPT_FAILED:
            return "Accept connection failed";
        case HEV_ERROR_NETWORK_SEND_FAILED:
            return "Send data failed";
        case HEV_ERROR_NETWORK_RECV_FAILED:
            return "Receive data failed";
        case HEV_ERROR_NETWORK_ADDRESS_IN_USE:
            return "Address already in use";
        case HEV_ERROR_NETWORK_CONNECTION_REFUSED:
            return "Connection refused";
        case HEV_ERROR_NETWORK_HOST_UNREACHABLE:
            return "Host unreachable";
            
        case HEV_ERROR_AUTH_INVALID_CREDENTIALS:
            return "Invalid authentication credentials";
        case HEV_ERROR_AUTH_FILE_NOT_FOUND:
            return "Authentication file not found";
        case HEV_ERROR_AUTH_FILE_READ_ERROR:
            return "Authentication file read error";
        case HEV_ERROR_AUTH_FILE_FORMAT_ERROR:
            return "Authentication file format error";
        case HEV_ERROR_AUTH_USER_NOT_FOUND:
            return "User not found";
            
        case HEV_ERROR_PROTOCOL_INVALID_VERSION:
            return "Invalid protocol version";
        case HEV_ERROR_PROTOCOL_INVALID_COMMAND:
            return "Invalid protocol command";
        case HEV_ERROR_PROTOCOL_INVALID_ADDRESS:
            return "Invalid protocol address";
        case HEV_ERROR_PROTOCOL_UNSUPPORTED_METHOD:
            return "Unsupported protocol method";
        case HEV_ERROR_PROTOCOL_MALFORMED_PACKET:
            return "Malformed protocol packet";
            
        case HEV_ERROR_FILE_NOT_FOUND:
            return "File not found";
        case HEV_ERROR_FILE_ACCESS_DENIED:
            return "File access denied";
        case HEV_ERROR_FILE_READ_ERROR:
            return "File read error";
        case HEV_ERROR_FILE_WRITE_ERROR:
            return "File write error";
        case HEV_ERROR_FILE_DELETE_ERROR:
            return "File delete error";
        case HEV_ERROR_FILE_ALREADY_EXISTS:
            return "File already exists";
            
        case HEV_ERROR_STRING_NULL_POINTER:
            return "String null pointer";
        case HEV_ERROR_STRING_BUFFER_OVERFLOW:
            return "String buffer overflow";
        case HEV_ERROR_STRING_INVALID_FORMAT:
            return "Invalid string format";
        case HEV_ERROR_STRING_TRUNCATED:
            return "String truncated";
            
        case HEV_ERROR_SYSTEM_RESOURCE_EXHAUSTED:
            return "System resource exhausted";
        case HEV_ERROR_SYSTEM_PERMISSION_DENIED:
            return "System permission denied";
        case HEV_ERROR_SYSTEM_NOT_IMPLEMENTED:
            return "System feature not implemented";
            
        default:
            return "Unknown error";
    }
}

int
hev_error_is_success(int error_code)
{
    return error_code == HEV_ERROR_SUCCESS;
}

int
hev_error_is_config_error(int error_code)
{
    return error_code <= HEV_ERROR_CONFIG_INVALID_FILE && 
           error_code >= HEV_ERROR_CONFIG_INVALID_PATH;
}

int
hev_error_is_network_error(int error_code)
{
    return error_code <= HEV_ERROR_NETWORK_SOCKET_FAILED && 
           error_code >= HEV_ERROR_NETWORK_HOST_UNREACHABLE;
} 