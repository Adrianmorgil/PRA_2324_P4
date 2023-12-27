#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include <string>
#include <list>

#include "/mnt/c/Users/adria/Desktop/Practicas programacion/PRA_2324_P1/ListLinked.h"

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;
	int max;
	ListLinked<TableEntry<V>>*table;
	int h(std::string key){
		std::size_t tamano = key.size();
		int x = 0;
		for(int i = 0; i < tamano; i++){
			char c = key.at(i);
			x = x + int(c);
		}
		return (x % max);
	}

    public:
        void insert(std::string key, V value){
		int i = h(key);
		for(const auto& p : *(table[i])){
			if(p.first == key){
				throw std::runtime_error("La clave ya existe en el diccionario");
			}
		}
		table[i]->push_back(std::make_pair(key, value));
	}
        V search(std::string key){
		int i = h(key);
		for(const auto& p : *(table[i])){
                	if(p.first == key){
                        	return p.second;
                        }
                }
		 throw std::runtime_error("La clave no se encuentra en el diccionario");
	}
        V remove(std::string key){
		int i = h(key);
		auto& list = *(table[i]);
		for(auto in = list.begin(); in != list.end(); ++in){
			if(in->first == key){
				list.erase(in);
				return;
			}
		}
		throw std::runtime_error("La clave no se encuentra en el diccionario");
	}
        int entries(){
		return n;
	}
        HashTable(){
		n = 0;
		for(int i = 0; i < max; i++){
			table[i] = new std::list<std::pair<std::string, V>>;
		}
	}
	~HashTable(){
		for(int i = 0; i < max; i++){
			delete table[i];
		}
	}
	int capacity(){
		return max;
	}
	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		out << th.n << " " << th.key << "=>" << th.value;
		return out;
	}
	V operator[] (std::string key){
	int i = h(key);
	for(const auto& p : *(table[i])){
		if(p.first == key && p. second != NULL){
			return p.second;
		}
	} 
	throw std::runtime_error("No existe valor asociado a esa clave");
	}
};

#endif 
