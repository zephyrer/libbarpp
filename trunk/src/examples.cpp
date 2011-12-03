// libbarpp examples
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the libbarpp project,
// licensed under GPLv2

#include "BarBitmapWin32.h"
#include "BarGeneratorEan8.h"
#include "BarGeneratorEan13.h"
#include "BarGeneratorCode25.h"
#include "BarGeneratorCode39.h"
#include "BarGeneratorCode93.h"
#include "BarGeneratorCode128.h"
#include "BarNoise.h"
#include "BarReader.h"
#include "BarReaderEan8.h"
#include "BarReaderEan13.h"
#include "BarReaderCode128.h"
#include "BarReaderCode39.h"
#include "BarReaderCode93.h"
#include "BarReaderCode25.h"

#include <iostream>

void example_ean8()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarGenerator* gen=new CBarGeneratorEan8(bmp);
	EAN8 ean8=1234567;
	
	try {
		gen->Generate(&ean8);
		bmp->Save("ean8.bmp");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete gen;
	delete bmp;
}

void example_ean13()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarGenerator* gen=new CBarGeneratorEan13(bmp);
	EAN13 ean13=123456789012;
	
	try {
		gen->Generate(&ean13);
		bmp->Save("ean13.bmp");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete gen;
	delete bmp;
}

void example_code128()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarGenerator* gen=new CBarGeneratorCode128(bmp);
	Code128 code128=new char[32];
	sprintf_s(code128, 32, "Dominik\0");
	
	try {
		gen->Generate(code128);
		bmp->Save("code128.bmp");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete[] code128;
	delete gen;
	delete bmp;
}

void example_code39()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarGenerator* gen=new CBarGeneratorCode39(bmp);
	Code39 code39=new char[32];
	sprintf_s(code39, 32, "DOMINIK\0");
	
	try {
		gen->Generate(code39);
		bmp->Save("code39.bmp");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete[] code39;
	delete gen;
	delete bmp;
}

void example_code93()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarGenerator* gen=new CBarGeneratorCode93(bmp);
	Code93 code93=new char[32];
	sprintf_s(code93, 32, "DOMINIK\0");
	
	try {
		gen->Generate(code93);
		bmp->Save("code93.bmp");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete[] code93;
	delete gen;
	delete bmp;
}

void example_code25()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarGenerator* gen=new CBarGeneratorCode25(bmp);
	Code25 code25=new char[32];
	sprintf_s(code25, 32, "1234567\0");
	
	try {
		gen->Generate(code25);
		bmp->Save("code25.bmp");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete[] code25;
	delete gen;
	delete bmp;
}

void example_noise_ean13()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarNoise* noise=new CBarNoise(bmp);

	try {
		bmp->Load("ean13.bmp");
		noise->injectNoise();
		bmp->Save("ean13.bmp");
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete noise;
	delete bmp;
}

void example_reader()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarReader* reader=new CBarReader(bmp);

	try {
		bmp->Load("ean13.bmp");
		reader->read();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete reader;
	delete bmp;
}

void example_reader_ean13()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarReaderEan13* reader=new CBarReaderEan13(bmp);

	try {
		bmp->Load("ean13.bmp");
		std::string code=reader->read(1);
		reader->check(code);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete reader;
	delete bmp;
}

void example_reader_ean8()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarReaderEan8* reader=new CBarReaderEan8(bmp);

	try {
		bmp->Load("ean8.bmp");
		std::string code=reader->read();
		reader->check(code);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete reader;
	delete bmp;
}

void example_reader_code128()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarReaderCode128* reader=new CBarReaderCode128(bmp);

	try {
		bmp->Load("code128.bmp");
		std::string code=reader->read();
		reader->check(code);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete reader;
	delete bmp;
}

void example_reader_code39()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarReaderCode39* reader=new CBarReaderCode39(bmp);

	try {
		bmp->Load("code39.bmp");
		std::string code=reader->read();
		reader->check(code);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete reader;
	delete bmp;
}

void example_reader_code93()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarReaderCode93* reader=new CBarReaderCode93(bmp);

	try {
		bmp->Load("code93.bmp");
		std::string code=reader->read();
		reader->check(code);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete reader;
	delete bmp;
}

void example_reader_code25()
{
	CBarBitmap* bmp=new CBarBitmapWin32;
	CBarReaderCode25* reader=new CBarReaderCode25(bmp);

	try {
		bmp->Load("code25.bmp");
		std::string code=reader->read();
		reader->check(code);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	delete reader;
	delete bmp;
}

int main()
{
	example_ean8();
	example_ean13();
	example_code128();
	example_code39();
	example_code93();
	example_code25();
	//example_noise_ean13();
	example_reader();
	example_reader_ean13();
	example_reader_ean8();
	example_reader_code128();
	example_reader_code39();
	example_reader_code93();
	example_reader_code25();

	std::cout << "Press any key...";
	std::cin.get();
	return 0;
}
