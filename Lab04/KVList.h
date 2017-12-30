/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: September 27, 2017				**
** OOP345 Section C - Workshop 4		**
** KVList.h								**
*****************************************/

#pragma once

template <typename K, typename V, int N>
class KVList {
	K keyArray[N];
	V valueArray[N];
	size_t count;
public:
	KVList() {
		count = 0;
	}

	size_t size() const {
		return count;
	}

	const K& key(int i) const {
		return keyArray[i];
	}

	const V& value(int i) const {
		return valueArray[i];
	}

	KVList& add(const K& k, const V& v) {
		if (count < N) {
			keyArray[count] = k;
			valueArray[count] = v;
			count++;
		}
		return *this;
	}

	int find(const K& k) const {
		for (size_t i = 0; i < count; i++) {
			if (keyArray[i] == k) {
				return i;
			}
		}
		return 0;
	}

	KVList& replace(int i, const K& k, const V& v) {
		if ((size_t)i < count) {
			keyArray[i] = k;
			valueArray[i] = v;
		}
		return *this;
	}
}; // class KVList