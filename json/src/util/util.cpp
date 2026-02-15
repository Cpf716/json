//
//  util.cpp
//  json
//
//  Created by Corey Ferguson on 6/30/25.
//

#include "util.h"

std::string decode(const std::string string) {
    if (string.empty())
        return string;

    // Find opening double quotations
    size_t l = 0;
    
    while (l < string.length() - 1 && (string[l] == '\\' || string[l] != '\"'))
        l++;
    
    // None found; return string
    if (l == string.length() - 1)
        return string;

    // Copy string
    size_t len = string.length() + 1;
    char*  str = new char[len];
    
    strcpy(str, string.c_str());
    
    // Erase opening double quotations
    for (size_t i = l; i < len - 1; i++)
        std::swap(str[i], str[i + 1]);
    
    len--;
    
    // Find closing double quotations
    size_t r = l;

    while (r < len - 2 && (str[r] == '\\' || str[r + 1] != '\"'))
        r++;

    // None found
    if (r == len - 2) {
        for (size_t i = l; i < len - 2; i++) {
            if (str[i] == '\\' && str[i + 1] == '\"') {
                for (size_t j = i; j < len - 1; j++)
                    std::swap(str[j], str[j + 1]);
                
                len--;
                i++;
            }
        }
    } else {
        // Erase closing double quotations
        for (size_t i = ++r; i < len - 1; i++)
            std::swap(str[i], str[i + 1]);

        len--;

        for (size_t i = l; i < r - 1; i++) {
            if (str[i] == '\\' && str[i + 1] == '\"') {
                for (size_t j = i; j < len - 1; j++)
                    std::swap(str[j], str[j + 1]);
                    
                len--;
                r--;
                i++;
            }
        }

        while (r < len - 2) {
            if (str[r] == '\\' && str[r + 1] == '\"') {
                for (size_t j = 0; j < 2; j++) {
                    for (size_t k = r; k < len - 1; k++)
                        std::swap(str[k], str[k + 1]);
                    
                    len--;
                }
            } else
                r++;
        }
    }

    std::string result = std::string(str);
    
    delete[] str;
    
    return result;
}

std::string encode(const std::string string) {
    size_t len = string.length() + 1;
    char*  str = new char[pow2((int) len + 2)];
    
    strcpy(str, string.c_str());
    
    // Insert leading double quotations
    str[len] = '\"';
    
    for (size_t i = len; i > 0; i--)
        std::swap(str[i], str[i - 1]);
    
    len++;
    
    // Escape double quotations
    for (size_t i = 1; i < len - 1; i++) {
        if (str[i] == '\"') {
            // resize, if required
            if (is_pow(len + 2, 2)) {
                char* tmp = new char[pow2((int) (len + 2) * 2)];

                for (size_t j = 0; j < len; j++)
                    tmp[j] = str[j];

                delete[] str;

                str = tmp;
            }

            // Insert escape character
            str[len] = '\\';
            
            for (size_t j = len; j > i; j--)
                std::swap(str[j], str[j - 1]);
            
            len++;
            i++;
        }
    }
    
    // Insert trailing double quotoations
    str[len] = '\"';
    
    std::swap(str[len], str[len - 1]);
    
    len++;

    std::string result = std::string(str);

    delete[] str;
    
    return result;
}

// 1. (\+|-)?
// 2. (\+|-)?[0-9]+
bool is_int(const std::string value) {
    int i = 0;
    
    // Leading positive (+) or negative (-) sign
    if (i != value.length() && (value[i] == '+' || value[i] == '-'))
        ++i;
    
    if (i == value.length())
        return false;
    
    for (; i < value.length(); i++)
        if (!isdigit(value[i]))
            return false;
    
    return true;
}

// 1. (\+|-)?
// 2. (\+|-)?[0-9]+(\.[0-9]+)?
// 3. (\+|-)?([0-9]+(\.[0-9]+)?|[0-9]*\.[0-9]+)((E|e)(\+|-)?[0-9]+)?
bool is_number(const std::string value) {
    if (value.empty())
        return false;
    
    int i = 0;
    
    // Leading positive (+) or negative (-) sign
    if (value[i] == '+' || value[i] == '-')
        ++i;
    
    // Find decimal point
    int j = i;
    
    while (j < value.length() && value[j] != '.')
        ++j;
    
    // If no decimal point is found, start at the beginning (after the sign, if applicable)
    // find exponent
    int k = j == value.length() ? i : j;
    
    while (k < value.length() && !(value[k] == 'E' || value[k] == 'e'))
        k++;
    
    // Stop at the decimal point, if applicable; otherwise stop at the exponent, if applicable
    int l = j < k ? j : k,
        m = i;
    
    for (; m < l; m++)
        if (!isdigit(value[m]))
            return false;
    
    // Count the number of digits between the beginning (after sign, if applicable) and the decimal point (if applicable)
    // and the decimal point (if applicable) and the exponent (if applicable)
    size_t n = l - i;
    
    //  After decimal (if applicable) and before exponent (if applicable)
    if (j != value.length()) {
        for (m = j + 1; m < k; m++)
            if (!isdigit(value[m]))
                return false;
        
        n += k - j - 1;
    }
    
    // There are no digits between sign (if applicable) and decimal point (if applicable)
    // and/or decimal point (if applicable) and exponent (if applicable)
    if (n == 0)
        return false;
    
    // After exponent (if applicable)
    if (k != value.length()) {
        size_t l = k + 1;
        
        if (l == value.length())
            return false;
        
        // Leading positive (+) or negative (-) sign
        if (value[l] == '+' || value[l] == '-')
            l++;
        
        if (l == value.length())
            return false;
        
        for (; l < value.length(); l++)
            if (!isdigit(value[l]))
                return false;
        // Single digit
    }
    
    return true;
}

bool is_pow(const size_t b, const size_t n) {
    if (b == 0)
        return false;
    
    if (n == 0)
        return b < 2;
    
    int result = log(b) / log(n);
    
    return (int) result - result == 0;
}

bool is_string(const std::string value) {
    return value.length() >= 2 && value[0] == '\"' && value[value.length() - 1] == '\"';
}

void merge(std::vector<std::string>& values, const std::string delimiter) {
    for (int i = 0; i < values.size() - 1; i++) {
        // Find opening double quotations
        size_t l = 0;
        
        while (l < values[i].length() && values[i][l] != '\"')
            l++;
        
        // Double quotations found
        if (l != values[i].length()) {
            // Find closing double quotations
            size_t j = l + 1;
            
            while (j < values[i].length()) {
                if (values[i][j] == '\"') {
                    size_t r = j + 1;
                    
                    while (r < values[i].length() && values[i][r] == '\"')
                        r++;
                    
                    if ((r - j) % 2 == 0)
                        j = r;
                    else
                        break;
                } else
                    j++;
            }
            
            // None found in the same token
            if (j == values[i].length()) {
                bool flag = true;
                
                // Find closing double quotations in subsequent tokens
                while (flag && i < values.size() - 1) {
                    size_t j = 0;
                    
                    while (j < values[i + 1].length()) {
                        if (values[i + 1][j] == '\"') {
                            size_t r = j + 1;
                            
                            while (r < values[i + 1].length() && values[i + 1][r] == '\"')
                                r++;
                            
                            if ((r - j) % 2 == 0)
                                j = r;
                            else {
                                // Break nested loop
                                flag = false;
                                break;
                            }
                        } else
                            j++;
                    }
                    
                    // Merge tokens
                    values[i] += delimiter + values[i + 1];

                    values.erase(values.begin() + i + 1);
                }
            }
        }
    }
}

double parse_number(const std::string value) {
    return is_number(value) ? stod(value) : NAN;
}

int parse_int(const std::string value) {
    return is_int(value) ? stoi(value) : INT_MIN;
}

int pow2(const int b) {
    if (b == 0)
        return 1;
    
    return pow(2, ceil(log(b) / log(2)));
}

std::string tolowerstr(std::string string) {
    std::transform(string.begin(), string.end(), string.begin(), ::tolower);

    return string;
}

std::string trim(const std::string string) {
    size_t start = 0;
    
    while (start < string.length() && isspace(string[start]))
        start++;
    
    size_t end = string.length();
    
    while (end > start && isspace(string[end - 1]))
        end--;
        
    return string.substr(start, end - start);
}
