#ifndef JACKREN_ZIP_PACK
#define JACKREN_ZIP_PACK

#include "include.hpp"
#include "utility.hpp"
#include "vector.hpp"
#include "bitmap.hpp"
#include "huffman_tree.hpp"

//jzpkѹ����
class ZipPacker {
private:
	Vector<int> _dicMap; //ÿ�ֽڶ�Ӧ��Ȩֵ
	Vector<bool> _byteExists; //�ֽ������Ƿ����
	HuffmanTree hffman; //Huffman��
	char* _filePath; //Դ�ļ�·��
	long long _originFileSize, _dictionarySize, _zippedDataSize; //����������Ϣ�洢����
	//��λͼbm�з���vec������������ѹ�������ƴ���Ϣ
	inline void sendData(BitMap& bm, Vector<unsigned char>& vec) {
		for (int i = 0; i < vec.size(); i++)bm.append(vec[i]);
	}
	//��λͼbm�з����ֽ�c�еĶ�������Ϣ
	inline void sendUCData(BitMap& bm, unsigned char c) {
		for (int i = 7; i >= 0; i--)bm.append((c >> i) & 1);
	}
public:
	//���캯��
	ZipPacker(const char* filePath) {
		int len = std::strlen(filePath);
		_filePath = new char[len + 5];
		std::strcpy(_filePath, filePath);
	}
	//��������
	~ZipPacker() {
		if (_filePath)delete[] _filePath;
	}
	//ɨ��Դ�ļ�
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
	//���huffman��������
	void build() {
		hffman.clear();
		for (int i = 0; i < 256; i++)hffman.insert(_dicMap[i], i);
		hffman.build();
	}
	//��zippedFilePath·��д��ѹ���ļ�
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
	//ѹ��������Ϣ����
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


