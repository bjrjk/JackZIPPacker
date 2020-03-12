#ifndef JACKREN_ZIP_UNPACK
#define JACKREN_ZIP_UNPACK

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "bitmap.hpp"
#include "trie_tree.hpp"

class ZipUnPacker {
private:
	Trie trie;
	char* _zippedFilePath;
	inline long long recvData(BitMap& bm, long long& ptr, Vector<unsigned char>& vec, long long dataSize) {
		vec.clear();
		int i;
		for (i = 0; i < dataSize && ptr < bm.size(); i++, ptr++) vec.append(bm.get(ptr));
		return i;
	}
	inline unsigned char recvUCData(BitMap& bm, long long& ptr) {
		int i;
		unsigned char c = 0;
		for (i = 0; i < 8&&ptr<bm.size(); i++,ptr++) {
			c <<= 1;
			c |= bm.get(ptr);
		}
		assert(i == 8);
		return c;
	}
public:
	ZipUnPacker(const char* zippedFilePath) {
		int len = std::strlen(zippedFilePath);
		_zippedFilePath = new char[len + 5];
		std::strcpy(_zippedFilePath, zippedFilePath);
	}
	~ZipUnPacker() {
		if (_zippedFilePath)delete[] _zippedFilePath;
	}
	bool unpack(const char* filePath) {
		BitMap bm;
		if (!bm.load(_zippedFilePath))return false;
		long long ptr = 0;
		unsigned char c;
		for (int i = 0; i < 256; i++) {
			c = recvUCData(bm, ptr);
			Vector<unsigned char> vec;
			recvData(bm, ptr, vec, c);
			trie.insert(vec, i);
		}
		FILE* f = fopen(filePath, "wb");
		if (!f)return false;
		while (ptr<bm.size()) {
			c = trie.bitmap_query(bm, ptr);
			fwrite(&c, 1, 1, f);
			ptr++;
		}
		fclose(f);
		return true;
	}
};


#endif


