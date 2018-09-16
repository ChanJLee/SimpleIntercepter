//
// Created by chan on 2018/9/16.
//

#include "SymbolTable.h"

template<typename V>
const V &SymbolTable<V>::lookup(const SymbolTable::String &k, const V &defaultValue)
{
	Iterator it = mMap.find(k);
	if (it != mMap.end()) {
		return it->second();
	}

	if (mParent == nullptr) {
		return defaultValue;
	}

	return mParent->lookup(k, defaultValue);
}

template<typename V>
SymbolTable<V>::SymbolTable(SymbolTable *parent)
	: mParent(parent)
{}

template<typename V>
void SymbolTable<V>::insert(const SymbolTable::String &k, const V &v)
{
	mMap[k] = v;
}
