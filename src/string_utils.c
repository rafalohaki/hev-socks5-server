/*
 ============================================================================
 Name        : string_utils.c
 Author      : hev <r@hev.cc>
 Copyright   : Copyright (c) 2017 - 2024 hev
 Description : Safe string utilities implementation
 ============================================================================
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "string_utils.h"

int
safe_strncpy(char *dest, const char *src, size_t dest_size)
{
    if (!dest || !src || dest_size == 0) {
        return -1;
    }

    size_t src_len = strlen(src);
    size_t copy_len = (src_len < dest_size - 1) ? src_len : dest_size - 1;
    
    memcpy(dest, src, copy_len);
    dest[copy_len] = '\0';
    
    return 0;
}

int
safe_strncat(char *dest, const char *src, size_t dest_size)
{
    if (!dest || !src || dest_size == 0) {
        return -1;
    }

    size_t dest_len = strlen(dest);
    size_t remaining = dest_size - dest_len - 1;
    
    if (remaining == 0) {
        return -1; /* No space left */
    }
    
    size_t src_len = strlen(src);
    size_t copy_len = (src_len < remaining) ? src_len : remaining;
    
    memcpy(dest + dest_len, src, copy_len);
    dest[dest_len + copy_len] = '\0';
    
    return 0;
}

int
validate_port(const char *port_str)
{
    if (!port_str || is_empty_string(port_str)) {
        return -1;
    }

    char *endptr;
    long port = strtol(port_str, &endptr, 10);
    
    if (*endptr != '\0') {
        return -1; /* Non-numeric characters */
    }
    
    if (port < 1 || port > 65535) {
        return -1; /* Invalid port range */
    }
    
    return 0;
}

int
validate_ip_address(const char *ip_str)
{
    if (!ip_str || is_empty_string(ip_str)) {
        return -1;
    }

    struct in_addr addr4;
    struct in6_addr addr6;
    
    /* Try IPv4 first */
    if (inet_pton(AF_INET, ip_str, &addr4) == 1) {
        return 0;
    }
    
    /* Try IPv6 */
    if (inet_pton(AF_INET6, ip_str, &addr6) == 1) {
        return 0;
    }
    
    return -1; /* Invalid IP address */
}

char *
trim_string(char *str)
{
    if (!str) {
        return NULL;
    }

    /* Trim leading whitespace */
    while (isspace((unsigned char)*str)) {
        str++;
    }
    
    if (*str == '\0') {
        return str; /* String was all whitespace */
    }
    
    /* Trim trailing whitespace */
    char *end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }
    
    end[1] = '\0';
    
    return str;
}

int
is_empty_string(const char *str)
{
    if (!str) {
        return 1;
    }
    
    while (*str) {
        if (!isspace((unsigned char)*str)) {
            return 0; /* Found non-whitespace character */
        }
        str++;
    }
    
    return 1; /* All whitespace or empty */
} 