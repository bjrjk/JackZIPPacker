#include "include.hpp"
#include "jack_zip_pack.hpp"
#include "jack_zip_unpack.hpp"
using namespace std;
void ZIP(const char* filePath, const char* ZIPFilePath) {
	ZipPacker zip(filePath);
	zip.scan();
	zip.build();
	zip.pack(ZIPFilePath);
	zip.report();
	exit(0);
}
void UnZIP(const char* ZIPFilePath, const char* filePath) {
	ZipUnPacker unzip(ZIPFilePath);
	unzip.unpack(filePath);
	exit(0);
}
void help() {
	cout << "---Jack ZIP Packer/UnPacker Help---" << endl;
	cout << "jzpk z [source filePath] [jzpk filePath]" << endl;
	cout << "jzpk u [jzpk filePath] [source filePath]" << endl;
	exit(0);
}
int main(int argc, char* argv[]) {
	if (argc != 4) help();
	if (strcmp(argv[1], "z") == 0)ZIP(argv[2], argv[3]);
	else if (strcmp(argv[1], "u") == 0)UnZIP(argv[2], argv[3]);
	else help();
}