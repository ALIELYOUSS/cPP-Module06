# C++ Module 06: Casts

A 42 cursus project exploring different types of casting and type conversion mechanisms in C++.

## Overview

This module focuses on understanding and implementing various casting techniques in C++, including:
- **Scalar type conversion** (implicit and explicit casting)
- **Pointer serialization** (converting pointers to integers)
- **Runtime Type Information (RTTI)** and polymorphism

## Project Structure

```
├── ex00/  - Scalar Type Conversion
├── ex01/  - Pointer Serialization
├── ex02/  - RTTI & Polymorphism
├── Makefile
└── README.md
```

## Exercises

### Exercise 00: Scalar Converter

**Objective:** Implement a static class that converts string literals to different scalar types.

**Features:**
- Converts string input to `char`, `int`, `float`, and `double`
- Handles special cases (overflow, underflow, `nan`, `inf`)
- Displays conversion results with proper formatting
- Private constructor (static class pattern)

**Files:**
- `ScalarConverter.hpp` - Class definition
- `ScalarConverter.cpp` - Implementation
- `main.cpp` - Test program

**Compilation:**
```bash
cd ex00
make
./convert "42"
./convert "4.2f"
./convert "nan"
```

**Usage:**
```cpp
ScalarConverter::convert("42");      // char: '*', int: 42, float: 42.0f, double: 42.0
ScalarConverter::convert("4.2f");    // int: 4, float: 4.2f, double: 4.2
ScalarConverter::convert("overflow"); // Handles impossible conversions
```

---

### Exercise 01: Serializer

**Objective:** Implement a static class that serializes and deserializes a Data pointer.

**Features:**
- Converts a `Data*` pointer to `uintptr_t` (serialization)
- Reconstructs the original `Data*` from `uintptr_t` (deserialization)
- Demonstrates pointer manipulation at the integer level
- Private constructor (static class pattern)

**Files:**
- `Serializer.hpp` - Class definition
- `Serializer.cpp` - Implementation
- `Data.hpp` - Data structure definition
- `main.cpp` - Test program

**Compilation:**
```bash
cd ex01
make
./serialize
```

**Usage:**
```cpp
Data* ptr = new Data();
uintptr_t raw = Serializer::serialize(ptr);
Data* restored = Serializer::deserialize(raw);
assert(ptr == restored); // Should be identical
delete ptr;
```

---

### Exercise 02: Identify Real Type

**Objective:** Implement a RTTI mechanism to identify object types at runtime and safely cast polymorphic pointers.

**Features:**
- Inheritance hierarchy: `Base` → `A`, `B`, `C`
- `generate()` function creates random derived class instances
- `identify()` functions (overloaded) determine the real type at runtime
- Demonstrates `dynamic_cast` and RTTI concepts
- Virtual destructors for proper cleanup

**Files:**
- `Base.hpp` - Base class and derived classes (A, B, C)
- `Base.cpp` - Implementation with identify functions
- `main.cpp` - Test program

**Compilation:**
```bash
cd ex02
make
./identify
```

**Usage:**
```cpp
Base* ptr = generate();           // Create random A, B, or C instance
identify(ptr);                    // Identify by pointer
identify(*ptr);                   // Identify by reference
```

---

## Key Concepts Covered

### Static Classes
All three classes follow the static pattern with private constructors to prevent instantiation.

### Type Conversion
- Implicit conversions
- Explicit casts (`static_cast`, `dynamic_cast`)
- Pointer to integer conversions (`reinterpret_cast`)

### RTTI (Run-Time Type Information)
- Virtual functions and destructors
- `dynamic_cast` for safe downcasting
- Type checking at runtime

### Memory Management
- Proper pointer handling
- Serialization/deserialization techniques
- Safe memory cleanup with virtual destructors

---

## Compilation

Each exercise can be compiled independently:

```bash
# Compile all exercises
make

# Compile specific exercise
cd ex00 && make && cd ..
cd ex01 && make && cd ..
cd ex02 && make && cd ..

# Clean all
make clean

# Clean everything including executables
make fclean
```

---

## Requirements

- C++98 standard (42 cursus requirement)
- No external libraries (except standard C++ library)
- G++ or Clang compiler

---

## Author

Created as part of the 42 cursus C++ piscine.

## License

This project is subject to 42 school's project license agreement.
