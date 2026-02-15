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
    auto array = new json::array({
        new object({{ "v", to_string(12) }}),
        new object({{ "v", to_string(11) }}),
        new object({{ "v", to_string(13) }}),
        new object({{ "v", to_string(5) }}),
        new object({{ "v", to_string(6) }})
    });

    // Perform insertion sort
    for (int i = 1; i < array->size(); i++) {
        for (int j = i - 1; j >= 0 && array->get(j)->number() > array->get(j + 1)->number(); j--) {
            auto temp = array->get(j);

            array->set(j, array->get(j + 1));
            array->set(j + 1, temp);
        }
    }

    cout << "json array: " << stringify(array) << endl;
    
    // Perform garbage collection
    delete array;
}
