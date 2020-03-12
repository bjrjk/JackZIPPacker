#ifndef JACKREN_ZIP_PACK
#define JACKREN_ZIP_PACK

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "bitmap.hpp"
#include "huffman_tree.hpp"

class ZipPacker {
private:
	Vector<int> _dicMap;
	HuffmanTree hffman;
	char* _filePath;
	long long _originFileSize, _dictionarySize, _zippedDataSize;
	inline void sendData(BitMap& bm, Vector<unsigned char>& vec) {
		for (int i = 0; i < vec.size(); i++)bm.append(vec[i]);
	}
	inline void sendUCData(BitMap& bm, unsigned char c) {
		for (int i = 7; i >= 0; i--)bm.append((c >> i) & 1);
	}
public:
	ZipPacker(const char* filePath) {
		int len = std::strlen(filePath);
		_filePath = new char[len + 5];
		std::strcpy(_filePath, filePath);
	}
	~ZipPacker() {
		if (_filePath)delete[] _filePath;
	}
	bool scan() {
		FILE* f = fopen(_filePath, "rb");
		if (!f)return false;
		_originFileSize = 0;
		_dicMap.clear();
		_dicMap.reserve(256);
		for (int i = 0; i < 256; i++)_dicMap[i] = 0;
		unsigned char c;
		while (fread(&c, 1, 1, f)) {
			_dicMap[c]++;
			_originFileSize++;
		}
		fclose(f);
		_originFileSize *= 8;
		return true;
	}
	void build() {
		hffman.clear();
		for (int i = 0; i < 256; i++)hffman.insert(_dicMap[i], i);
		hffman.build();
	}
	bool pack(const char* zippedFilePath) {
		BitMap bm;
		FILE* f = fopen(_filePath, "rb");
		if (!f)return false;
		_dictionarySize = 0;
		_zippedDataSize = 0;
		unsigned char c;
		for (int i = 0; i < 256; i++) {
			Vector<unsigned char> vec = hffman.query(i);
			assert(vec.size() < 256);
			c = vec.size();
			sendUCData(bm, c);
			_dictionarySize += 8;
			sendData(bm, vec);
			_dictionarySize += vec.size();
		}
		while (fread(&c, 1, 1, f)) {
			Vector<unsigned char> vec = hffman.query(c);
			sendData(bm, vec);
			_zippedDataSize += vec.size();
		}
		fclose(f);
		bm.pack(zippedFilePath);
		return true;
	}
	void report() {
		std::cout << "---Jack ZIP Packer Compression Information---" << std::endl;
		std::cout << "Origin File Size: (Bit) " << _originFileSize << std::endl;
		std::cout << "Huffman Tree Dictionary Size: (Bit) " << _dictionarySize << std::endl;
		std::cout << "Zipped Data Size: (Bit) " << _zippedDataSize << std::endl;
		std::cout << "Zipped File Size: (Bit) " << (_zippedDataSize + _dictionarySize + sizeof(long long)) << std::endl;
		std::cout << "ZIP Rate: " << (_zippedDataSize + _dictionarySize + sizeof(long long)) * 100 / _originFileSize << "%" << std::endl;
	}
};


#endif


