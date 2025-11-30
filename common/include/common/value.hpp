#pragma once

// Enum representing primitive data types supported by the language.
enum PrimitiveType {
    PT_U8,  // Unsigned 8-bit integer data type
    PT_I8,  // Signed 8-bit integer data type
    PT_U16, // Unsigned 16-bit integer data type
    PT_I16, // Signed 16-bit integer data type
    PT_U32, // Unsigned 32-bit integer data type
    PT_I32, // Signed 32-bit integer data type
    PT_U64, // Unsigned 64-bit integer data type
    PT_I64, // Signed 64-bit integer data type
    PT_F32, // 32-bit floating-point data type
    PT_F64  // 64-bit floating-point data type
};

// Enum representing data type categories.
enum TypeCategory {
    TC_PRIMITIVE    // Primitive data type
};

// Struct being a logical representation of a data type.
struct DataType {
    TypeCategory category;
    union {
        PrimitiveType primitive;
    } type;
};

// Macro definitions of all primitive data types. These definitions are temporary.
#define uint8 unsigned char
#define int8 char
#define uint16 unsigned short int
#define int16 short int
#define uint32 unsigned int
#define int32 int
#define float32 float
#define uint64 unsigned long long int
#define int64 long long int
#define float64 double

// Union type representing single 64-bit value.
union Value {
    uint8 uint8v;
    int8 int8v;
    uint16 uint16v;
    int16 int16v;
    uint32 uint32v;
    int32 int32v;
    float32 float32v;
    uint64 uint64v;
    int64 int64v;
    float64 float64v;
};