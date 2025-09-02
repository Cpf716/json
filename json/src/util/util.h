//
//  util.h
//  json
//
//  Created by Corey Ferguson on 6/30/25.
//

#ifndef util_h
#define util_h

#include <cassert>
#include <iostream>
#include <sstream>

// Non-Member Functions

/**
 * Decode double quotation-escaped string
 */
std::string              decode(const std::string string);

/**
 * Return string escaped by double quotations
 */
std::string              encode(const std::string string);

/**
 * Merge double quotation-escaped tokens
 */
void                     merge(std::vector<std::string>& values, const std::string delimiter = "");

/**
 * Return the next power of two
 */
int                      pow2(const int b);

/**
 * Return string trimmed of leading and trailing whitespace
 */
std::string              trim(const std::string string);

/**
 * Return true if value can be parsed into a floating-point number, otherwise return false
 */
bool                     is_number(const std::string value);

/**
 * Return true if value is not a number, otherwise return false
 */
bool                     is_string(const std::string value);

/**
 * Return true if value includes double quotations, otherwise return false
 */
bool                     is_string_literal(const std::string value);

/**
 * Return true if value can be parsed into an integer, otherwise return false
 */
bool                     is_int(const std::string value);

/**
 * Return value parsed into a floating-point number
 */
double                   parse_number(const std::string value);

/**
 * Return value parsed into an integer
 */
int                      parse_int(const std::string value);

bool                     is_pow(const size_t b, const size_t n);

#endif /* util_h */
