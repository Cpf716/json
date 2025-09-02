//
//  json.h
//  json
//
//  Created by Corey Ferguson on 6/30/25.
//

#ifndef json_h
#define json_h

#include <cassert>
#include <map>
#include "util.h"

namespace json {
    // Typedef

    struct object {        
        enum type { array_t, object_t, primitive_t };
        
        // Constructors
        
        object();
        
        object(const std::string key);

        /**
         * options:
         * - (k)ey
         * - (t)ext
         * - (v)alue
         */
        object(std::map<std::string, std::string> options);

        object(const enum type type);
        
        object(const std::string key, const enum type type);
        
        object(const std::string key, const std::string value);

        object(const std::vector<object*> values, const enum type type = object_t);

        // Member Functions

        /**
         * Set undefined
         */
        void                 erase();

        /**
         * Set item undefined
         */
        void                 erase(const size_t index);
        
        /**
         * Delete property
         */
        void                 erase(const std::string key);
        
        /**
         * Deallocate object
         */
        void                 free();

        /**
         * Return property if it exists, otherwise return NULL
         */
        object*              get(std::string key);

        std::string          key();

        bool                 null();

        void                 nullify();
                
        /**
         * Delete undefined properties
         */
        object*              sanitize();

        /**
         * Set array item or object property and return it
         */
        object*              set(object* value);
        
        /**
         * Return array size
         */
        size_t               size();

        type&                type();
        
        bool                 undefined();

        std::string&         value();
        
        std::vector<object*> values();
    protected:
        // Member Fields

        std::string          _key;
        std::vector<object*> _values;
    private:
        // Member Fields
        
        std::vector<std::pair<std::string, size_t>> _key_map;
        enum type                                   _type = primitive_t;
        std::string                                 _value;
        
        // Member Functions

        void                                         _erase(const size_t index);

        /**
         * Perform binary search and return the relative index of key
         */
        int                                          _find(const std::string key);
        
        int                                          _find(const std::string key, const int start, const int end);

        /**
         * Build key map
         */
        void                                         _map_keys();

        /**
         * Parse JSON string to object
         */
        void                                         _parse(const std::string text);
        
        object*                                      _parse(object* target, std::vector<std::string>& source, const size_t start, const size_t end);
    };

    class array: public object {
        // Member Functions

        json::array* _splice(const int start, const int delete_count, const std::vector<object*> values);
    public:
        // Typedef

        struct iterator {
            // Constructors

            iterator(const size_t size, std::vector<object*> values);

            // Operators

            object*   operator*() const;

            // object*   operator->() const;

            iterator& operator+(int value);

            iterator& operator++();

            iterator& operator++(int);

            iterator& operator-(int value);

            iterator& operator--();

            iterator& operator--(int);

            bool      operator==(const iterator& value) const;

            bool      operator!=(const iterator& value) const;
        private:
            // Member Fields

            int                  _index = 0;
            size_t               _size;
            std::vector<object*> _values;
        };

        // Constructors
        
        array();
        
        array(const std::string key);

        array(const size_t size);

        array(const std::vector<object*> values);

        // Member Functions

        object*      at(const int index);

        iterator     begin();

        json::array* concat(std::vector<object*> values);

        iterator     end();

        /**
         * Return property if it exists, otherwise return NULL
         */
        object*      get(std::string key);

        /**
         * Return value at index if it exists, otherwise return NULL
         */
        object*      get(const size_t index);

        /**
         * Set array item or object property and return it
         */
        object*      set(object* value);

        /**
         * Shorthand for array items
         */
        object*      set(const size_t index, object* value);

        json::array* slice(const int start);

        json::array* slice(int start, int end);

        json::array* splice(int start);

        json::array* splice(const int start, const int delete_count);
        
        json::array* splice(int start, int delete_count, const std::vector<object*> values);
    };

    // Non-Member Functions

    object*                                      assign(object* target, object* source);

    std::vector<std::pair<std::string, object*>> entries(object* value);

    std::vector<std::string>                     keys(object* value);

    std::string                                  null();

    object*                                      parse(const std::string text);

    std::string                                  stringify(object* value);

    std::string                                  type_str(object* value);

    std::vector<object*>                         values(object* value);
}

#endif /* json_h */
