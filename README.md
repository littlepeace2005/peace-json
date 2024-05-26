# peace-json

## Introduction
`peace-json` is a lightweight, open source JSON library written in C++. It offers efficient JSON deserialization and serialization capabilities for projects requiring fast and flexible JSON handling.

## Features
- **Fast Deserialization**: Efficiently parses JSON string.
- **Simple Serialization**: Easily converts C++ objects back into JSON string.
- **STL Integration**: Seamlessly integrates with C++ STL, with strings, objects, and arrays derived from `std::string`, `std::unordered_map`, and `std::vector`.

## Getting Started
To use `peace-json` in your project, follow these steps:

### Prerequisites
C++ compiler that supports C++11 or later.

### Installation
1. Clone the repository:
   ```
   git clone https://github.com/littlepeace2005/peace-json.git
   ```
2. Include the library in your project:
   ```cpp
   #include "json.h"
   ```

### Usage
#### Parsing JSON
```cpp
std::string personStr = R"(
  {
    "name": "John Smith",
    "age": 27,
    "is_alive": true,
    "address": {
      "street_address": "21 2nd Street",
      "city": "New York",
      "state": "NY",
      "postal_code": "10021-3100"
    },
    "phone_numbers": [
      {
        "type": "home",
        "number": "212 555-1234"
      },
      {
        "type": "office",
        "number": "646 555-4567"
      }
    ],
    "children": [
      "Catherine",
      "Thomas",
      "Trevor"
    ],
    "spouse": null
  }
)";

peace::Json person = peace::Json::parse(peronStr);
```

#### Stringifying JSON
```cpp
peace::Json person = peace::JsonObject{
  {"name", "John Smith"},
  {"age", 27},
  {"is_alive", true},
  {"address", peace::JsonObject{
    {"street_address", "21 2nd Street"},
    {"city", "New York"},
    {"state", "NY"},
    {"postal_code", "10021-3100"}
  }},
  {"phone_numbers", peace::JsonArray{
    peace::JsonObject{
      {"type", "home"},
      {"number", "(212)555-1234"}
    },
    peace::JsonObject{
      {"type", "office"},
      {"number", "(646)555-4567"}
    }
  }},
  {"children", peace::JsonArray{
    "Catherine",
    "Thomas",
    "Trevor"
  }},
  {"spouse", peace::JsonNull()}
};

std::string personStr = peace::Json::stringify(person);
```

#### Reading from and Writing to Files
This example demonstrates how to read JSON from a file, modify its content, and then write it to stdout.
##### template.json
```json
{
  "name": null,
  "age": null,
  "is_alive": null,
  "address": {},
  "phone_numbers": [
    {"type": "home", "number": null},
    {"type": "office", "number": null}
  ],
  "children": [],
  "spouse": null
}
```
##### main.cc
```cpp
#include <fstream>
#include <iostream>
#include "json.h"
using namespace peace;

int main() try
{
  std::fstream file;
  Json person;

  // read JSON from a file
  file.open("template.json", std::ios_base::in);
  if (file) {
    file >> person; file.close();
  } else
    throw std::runtime_error("Failed to open the file");

  // modify JSON data
  person["name"] = "John Smith";
  person["is_alive"] = true;
  person["age"] = 27;
  person["address"]["street_address"] = "21 2nd Street";
  person["address"]["city"] = "New York";
  person["address"]["state"] = "NY";
  person["address"]["postal_code"] = "10021-3100";
  person["phone_numbers"][0]["number"] = "212 555-1234";
  person["phone_numbers"][1]["number"] = "646 555-4567";
  person["children"].asArray() = {"Catherine", "Thomas", "Trevor"};

  // write modified JSON to a file
  file.open(person["name"].asString() + ".json", std::ios_base::out);
  if (file) {
    file << person; file.close();
  } else
    throw std::runtime_error("Failed to open the file");
  
  return EXIT_SUCCESS;
}
catch(const std::exception &e)
{
  // exception handling
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
```

## Contributing
Contributions are welcome.

## License
`peace-json` is licensed under the MIT License. See the LICENSE file for more details.
