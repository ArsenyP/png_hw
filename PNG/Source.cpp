#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <stdint.h>
#include <intrin.h>
#include <vector>
#include <stdint.h>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

using namespace std;
void CHUNK_name(ifstream& file, char* name) {

	//char name[5];

	file.read(name, 4);
	if (memcmp(name, "IHDR", 4) == 0)
		cout << "Name is: IHDR " << endl;
	else if (memcmp(name, "IDAT", 4) == 0)
		cout << "Name is: IDAT" << endl;
	else if (memcmp(name, "IEND", 4) == 0)
		cout << "Name is: IEND" << endl;
	//return name;
}

int CHUNK_length(ifstream& file) {

	char length[4];

	file.read(length, 4);
	int size = (length[0] << 24) | (length[1] << 16) | (length[2] << 8) | (length[3]);//сдвиг битов
	cout << "Length is: " << size << endl;
	return size;
}

void CHUNK_CRC(ifstream& file,int size) {

	unsigned char CRC[4];

	file.seekg((int)file.tellg() + size);//tellg- говорит позицию от которой необходимо оттолкнуться
	file.read((char*)CRC, 4);
	for (int x = 0; x < 4; x++)
		cout << "CRC: " << hex << int(CRC[x]) << endl;//выведет побайтово!
}

int main() {
	setlocale(0, "");
	int size;
	char PNG_signature[8];
	char Signature_code[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
	char length[4];
	char name[5];
	unsigned char CRC[4];
	/*******************************************************************************************************************************/
	ifstream file;
	file.open("c:\\LETI\\normal_file.png", ios_base::binary | ios_base::in);//(в скобки необходимо прописать свой путь к изображению)
	/*******************************************************************************************************************************/
	file.read(PNG_signature, 8); 
	if (memcmp(PNG_signature, Signature_code, 8) == 0)
		cout << "PNG Signature is correct!"<<endl;
	else                                    // Сравниваем первые 8 байт массивов
	                                        // и результат выводим на экран
		cout << "PNG Signature is wrong!";
	
	/*******************************************************************************************************************************/
	//проверка на наличие чанков
	
	/*******************************************************************************************************************************/
	int Counter=0;
	while (file.good()) {
		cout << "address: " << hex << (int)file.tellg() << endl;
		
		size=CHUNK_length(file);
		CHUNK_name(file, name);
		CHUNK_CRC(file, size);
		if (memcmp(name, "IDAT", 4) == 0)
			Counter++;
			 
	
		if (memcmp(name, "IEND", 4) == 0)
			break;
		//_getch();
	}
	_getch();
	return 0;
}