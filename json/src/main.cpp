//
//  main.cpp
//  json
//
//  Created by Corey Ferguson on 6/30/25.
//

#include <iostream>
#include "json.h"

using namespace json;
using namespace std;

int main(int argc, const char * argv[]) {
    // Initialize array
    auto array = new json::array((vector<object*>) {
        new object({{ "v", to_string(12) }}),
        new object({{ "v", to_string(11) }}),
        new object({{ "v", to_string(13) }}),
        new object({{ "v", to_string(5) }}),
        new object({{ "v", to_string(6) }})
    });

    // Perform insertion sort
    for (int i = 1; i < array->size(); i++) {
        for (int j = i - 1; j >= 0 && parse_int(array->get(j)->value()) > parse_int(array->get(j + 1)->value()); j--) {
            auto temp = array->get(j);

            array->set(j, array->get(j + 1));
            array->set(j + 1, temp);
        }
    }

    json::array* temp = array->concat((std::vector<object*>) {
        new json::array((vector<object*>) {
            new object((vector<object*>){
                new object("value", std::to_string(99))
            })
        }) 
    });

    cout << stringify(temp) << endl;
    
    // Perform garbage collection
    temp->free();
    
    // Dereference concatenated items
    array->erase();
    
    // Perform garbage collection
    array->free();
}
