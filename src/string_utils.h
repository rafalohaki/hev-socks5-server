/*
 ============================================================================
 Name        : string_utils.h
 Author      : hev <r@hev.cc>
 Copyright   : Copyright (c) 2017 - 2024 hev
 Description : Safe string utilities
 ============================================================================
 */

#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <stddef.h>

/**
 * @brief Safely copy a string with null termination guarantee
 * @param dest Destination buffer
 * @param src Source string
 * @param dest_size Size of destination buffer
 * @return 0 on success, -1 on error
 */
int safe_strncpy(char *dest, const char *src, size_t dest_size);

/**
 * @brief Safely concatenate strings with null termination guarantee
 * @param dest Destination buffer
 * @param src Source string to append
 * @param dest_size Size of destination buffer
 * @return 0 on success, -1 on error
 */
int safe_strncat(char *dest, const char *src, size_t dest_size);

/**
 * @brief Validate if a string represents a valid port number
 * @param port_str Port string to validate
 * @return 0 if valid, -1 if invalid
 */
int validate_port(const char *port_str);

/**
 * @brief Validate if a string represents a valid IP address
 * @param ip_str IP address string to validate
 * @return 0 if valid, -1 if invalid
 */
int validate_ip_address(const char *ip_str);

/**
 * @brief Trim whitespace from both ends of a string
 * @param str String to trim (modified in place)
 * @return Pointer to trimmed string
 */
char *trim_string(char *str);

/**
 * @brief Check if string is empty or contains only whitespace
 * @param str String to check
 * @return 1 if empty/whitespace only, 0 otherwise
 */
int is_empty_string(const char *str);

#endif /* __STRING_UTILS_H__ */ 