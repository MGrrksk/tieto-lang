#pragma once

// Enum representing all data types supported by the language.
enum DataType {
    DT_U8,  // Unsigned 8-bit integer data type
    DT_I8,  // Signed 8-bit integer data type
    DT_U16, // Unsigned 16-bit integer data type
    DT_I16, // Signed 16-bit integer data type
    DT_U32, // Unsigned 32-bit integer data type
    DT_I32, // Signed 32-bit integer data type
    DT_U64, // Unsigned 64-bit integer data type
    DT_I64, // Signed 64-bit integer data type
    DT_F32, // 32-bit floating-point data type
    DT_F64, // 64-bit floating-point data type
    DT_DYN  // Dynamic data type
};

// Enum representing basic data types differentiated in implementation.
enum ValueType {
    VT_UINT,    // 64-bit unsigned integer value type
    VT_INT,     // 64-bit signed integer value type
    VT_FLOAT    // 64-bit floating-point value type
};

#define uint64 unsigned long long   // This definition is temporary.
#define int64 long long int         // This definition is temporary.
#define float64 double              // This definition is temporary.

// Union type representing single 64-bit value.
union Value {
    // Field for `VT_UINT` value type.
    uint64 uintv;
    // Field for `VT_INT` value type.
    int64 intv;
    // Field for `VT_FLOAT` value type.
    float64 floatv;
};