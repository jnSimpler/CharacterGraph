#pragma once

#include "MyForm.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <iosfwd>
#include <sstream>
#include <msclr\marshal.h>
#include <vcclr.h>
#using <mscorlib.dll>

using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Drawing::Drawing2D;

class ImgData
{
private:
	bool Existing;
	gcroot<Bitmap ^> img;
public:
	void Create(Bitmap^ bitmap)
	{
		this->Existing = true;
		img = gcnew Bitmap(bitmap);
	};
	void Create(String^ FileName)
	{
		this->Existing = true;
		img = gcnew Bitmap(FileName, true);
	}
	ImgData()
	{
		this->Existing = false;
	}
	Bitmap^ GetData()
	{
		return this->img;
	}
	int GetW()
	{
		return this->img->Width;
	}
	int GetH()
	{
		return this->img->Height;
	}
	void Proceed()
	{

	}
	void Delete()
	{
		this->Existing = false;
		delete this->img;
	};
} IData;
