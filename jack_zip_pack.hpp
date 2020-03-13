#ifndef JACKREN_ZIP_PACK
#define JACKREN_ZIP_PACK

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "bitmap.hpp"
#include "huffman_tree.hpp"

//jzpk压缩类
class ZipPacker {
private:
	Vector<int> _dicMap; //每字节对应的权值
	Vector<bool> _byteExists; //字节数据是否存在
	HuffmanTree hffman; //Huffman树
	char* _filePath; //源文件路径
	long long _originFileSize, _dictionarySize, _zippedDataSize; //报告性能信息存储变量
	//向位图bm中发送vec中所含的所有压缩二进制串信息
	inline void sendData(BitMap& bm, Vector<unsigned char>& vec) {
		for (int i = 0; i < vec.size(); i++)bm.append(vec[i]);
	}
	//向位图bm中发送字节c中的二进制信息
	inline void sendUCData(BitMap& bm, unsigned char c) {
		for (int i = 7; i >= 0; i--)bm.append((c >> i) & 1);
	}
public:
	//构造函数
	ZipPacker(const char* filePath) {
		int len = std::strlen(filePath);
		_filePath = new char[len + 5];
		std::strcpy(_filePath, filePath);
	}
	//析构函数
	~ZipPacker() {
		if (_filePath)delete[] _filePath;
	}
	//扫描源文件
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
		_byteExists.clear();
		_byteExists.reserve(256);
		for (int i = 0; i < 256; i++)_byteExists[i] = _dicMap[i] > 0;
		_originFileSize *= 8;
		return true;
	}
	//完成huffman建树操作
	void build() {
		hffman.clear();
		for (int i = 0; i < 256; i++)hffman.insert(_dicMap[i], i);
		hffman.build();
	}
	//在zippedFilePath路径写入压缩文件
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
			if (_byteExists[i]) {
				c = vec.size();
				sendUCData(bm, c);
				_dictionarySize += 8;
				sendData(bm, vec);
				_dictionarySize += vec.size();
			}
			else {
				sendUCData(bm, 0);
				_dictionarySize += 8;
			}
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
	//压缩性能信息报告
	void report() {
		std::cout << "---Jack ZIP Packer v0.2 Compression Information---" << std::endl;
		std::cout << "---Designed and Programmed by Jack Ren, https://renjikai.com/ ---" << std::endl;
		std::cout << "Origin File Size: " << _originFileSize << " Bits"<<std::endl;
		std::cout << "Huffman Tree Dictionary Size: " << _dictionarySize << " Bits" << std::endl;
		std::cout << "Zipped Data Size: " << _zippedDataSize << " Bits" << std::endl;
		std::cout << "Zipped File Size: " << (_zippedDataSize + _dictionarySize + sizeof(long long)) << " Bits" << std::endl;
		std::cout << "ZIP Rate: " << (_zippedDataSize + _dictionarySize + sizeof(long long)) * 100 / _originFileSize << "%" << std::endl;
	}
};


#endif


