//
// Created by chan on 2018/9/16.
//

#ifndef SIMPLEINTERPRETER_SYMBOLTABLE_H
#define SIMPLEINTERPRETER_SYMBOLTABLE_H

#include <map>
#include <string>

#ifdef DEBUG
#include <iostream>
#endif

template<typename V>
class SymbolTable
{
public:
	typedef std::string String;
	typedef std::map<String, V> KVMap;
	typedef typename KVMap::iterator Iterator;
private:
	KVMap mMap;
	SymbolTable *mParent;
	String mName;
public:
	SymbolTable(const String &name, SymbolTable *parent);
	V &lookup(const String &k, V &defaultValue);
	bool insert(const String &k, const V &v);

#ifdef DEBUG
	const KVMap &getMap();
#endif
};

template<typename V>
V &SymbolTable<V>::lookup(const SymbolTable::String &k, V &defaultValue)
{
	Iterator it = mMap.find(k);
	if (it != mMap.end()) {
		return it->second;
	}

	if (mParent == nullptr) {
		return defaultValue;
	}

	return mParent->lookup(k, defaultValue);
}

template<typename V>
SymbolTable<V>::SymbolTable(const String &name, SymbolTable *parent)
	: mParent(parent), mName(name)
{}

template<typename V>
bool SymbolTable<V>::insert(const SymbolTable::String &k, const V &v)
{
	if (mMap.find(k) != mMap.end()) {
		return false;
	}

	mMap[k] = v;
	return true;
}

#ifdef DEBUG
template<typename V>
const typename SymbolTable<V>::KVMap &SymbolTable<V>::getMap()
{
	return mMap;
}
#endif


#endif //SIMPLEINTERPRETER_SYMBOLTABLE_H
