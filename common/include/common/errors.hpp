#pragma once

// Enum type representing error codes for all errors supported by the language.
enum ErrorCode {
    EC_NONE,
    EC_MISSING_EXPR,
    EC_MISSING_RPAREN
};

// Array of error messages for every error code.
const char* const ERROR_MESSAGES[] = {
    nullptr,
    "Missing expression",
    "Unclosed parenthesis"
};