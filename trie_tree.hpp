#ifndef JACKREN_TRIE
#define JACKREN_TRIE

#include "include.hpp"
#include "bitmap.hpp"
#include "vector.hpp"

class Trie {
private:
	int trie[2000][2];
	unsigned char data[2000];
	bool hasData[2000];
	int tot;
public:
	Trie():tot(0) {
		std::memset(trie, 0, sizeof(trie));
		std::memset(hasData, false, sizeof(hasData));
	}
	void insert(Vector<unsigned char>& s, unsigned char v) {
		int node = 0;
		for (int i = 0; i < s.size(); i++) {
			if (!trie[node][s[i]])node = trie[node][s[i]] = ++tot;
			else node = trie[node][s[i]];
		}
		hasData[node] = true;
		data[node] = v;
	}
	unsigned char query(Vector<unsigned char>& s) {
		int node = 0;
		for (int i = 0; i < s.size(); i++) {
			assert(trie[node][s[i]]);
			node = trie[node][s[i]];
		}
		assert(hasData[node]);
		return data[node];
	}
	unsigned char bitmap_query(BitMap& bm,long long & ptr) {
		int node = 0;
		for (; ptr < bm.size(); ptr++) {
			assert(trie[node][bm.get(ptr)]);
			node = trie[node][bm.get(ptr)];
			if (hasData[node])break;
		}
		assert(hasData[node]);
		return data[node];
	}
};

#endif