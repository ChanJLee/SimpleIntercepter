//
// Created by chan on 2018/9/16.
//

#ifndef SIMPLEINTERPRETER_SYMBOLTABLE_H
#define SIMPLEINTERPRETER_SYMBOLTABLE_H

#include <map>
#include <string>

template <typename V>
class SymbolTable
{
public:
	typedef std::string String;
	typedef std::map<String, V> KVMap;
	typedef typename KVMap::iterator Iterator;
private:
	KVMap mMap;
	SymbolTable *mParent;
public:
	SymbolTable(SymbolTable *parent);
	const V& lookup(const String& k, const V& defaultValue);
	void insert(const String& k, const V& v);
};




#endif //SIMPLEINTERPRETER_SYMBOLTABLE_H
