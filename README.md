# JSON SDK for C++

Thanks for checking out my JSON SDK for C++!

It SDK enables C++ developers to natively handle JSON objects, whether for API integration, database operations, etc.

## Examples

### Parse JSON
```
#include "json.h"

using namespace json;

auto customer = parse("{ \"firstName\": \"Sam\", \"lastName\": \"Smith\", \"preferredName\": \"Sam\" }");

// Alternatively, you can use the object constructor

auto customer = new object({{ "t", "{ \"firstName\": \"Sam\", \"lastName\": \"Smith\", \"preferredName\": \"Sam\" }" }});

// Output: { customer: { firstName: "Sam", lastName: "Smith", fullName: "Sam Smith", preferredName: "Sam" }}
```

### Perform Garbage Collection
```
// Always delete top-level objects at the end of their use

delete fruit;
```

### Declare Properties
```
auto first_name = decode(customer->get("firstName")->value()),
     last_name = decode(customer->get("lastName")->value());

customer->set(new object("fullName", encode(first_name + " " + last_name)));

// Declare anonymous value
auto phone = new object({{ "v", encode("6781234567") }})

auto phones = new json::array((std::vector<object*>) {
    phone
});

phones->key() = "phones";

customer->set(phones);

// Output: { customer: { firstName: "Sam", lastName: "Smith", fullName: "Sam Smith", preferredName: "Sam", phones: ["6781234567"] }}
```

### Delete Properties
```
// Set undefined

customer->get("preferredName")->erase();

// Output: { customer: { firstName: "Sam", lastName: "Smith", fullName: "Sam Smith", preferredName: undefined, phones: ["6781234567"] }}

// Delete property

customer->erase("preferredName");

// Output: { customer: { firstName: "Sam", lastName: "Smith", fullName: "Sam Smith", phones: ["6781234567"] }}
```

### Assign Properties
```
auto emails = new json::array((std::vector<object*>) {
    new object({{ "v", encode("sam-smith@example.com") }})
})

assign(customer, emails);

// Output: { customer: { firstName: "Sam", lastName: "Smith", fullName: "Sam Smith", phones: ["6781234567"], "0": ["sam-smith@example.com"] }}
```

### Convert Objects to String
```
stringify(customer);
```

### Arrays
```
auto fruit = new json::array((std::vector<object*>) {
    new object({{ "v", encode("apple") }}),
    new object({{ "v", encode("banana") }})
});

// Output: ["apple", "banana"]
```

#### Append Items
```
fruit->set(new object({{ "v", encode("orange) }}));

// Output: ["apple", "banana", "orange"]

// Assign a non-negative integer key to set or replace an item, resize an array (n - 1), or to push an item

// Initialize object with key: n
auto pear = new object(std::to_string(fruit->size()));

pear->value() = encode("pear");

fruit->set(pear);

// Output: ["apple", "banana", "orange", "pear"]
```

#### Assign Properties
```
object* pineapple = new object({
    new object("name", encode("pineapple"))
});

fruit->set(pineapple);

// Output: ["apple", "banana", "orange", "pear", { "name": "pineapple" }]
```

#### Delete Items
```
fruit->splice(1, 1);

// Output: ["apple", "orange", "pear", { "name": "pineapple" }]

fruit->splice(-1);

// Output: ["apple", "orange", { "name": "pineapple" }]
```
