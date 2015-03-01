#pragma once

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

using namespace cli;
using namespace std;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Drawing::Drawing2D;
using namespace System::IO;
using namespace System::Text;

namespace ImgDataTech
{
	typedef System::Drawing::Rectangle Rectangle;

	string SStringToSTLString(String^ str)
	{
		return (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
	};

	class ImageFunctions
	{
	public:
		ImageFormat^ GetImageFormat(string extension)
		{
			Guid result;

			switch (extension[1])
			{
			case 'p':
				result = ImageFormat::Png->Guid;
				break;
			case 'j':
				result = ImageFormat::Jpeg->Guid;
				break;
			case 'g':
				result = ImageFormat::Gif->Guid;
				break;
			case 't':
				result = ImageFormat::Tiff->Guid;
				break;
			default: // bmp, rle, dib
				result = ImageFormat::Bmp->Guid;
				break;
			}

			return gcnew ImageFormat(result);
		}
	};

	class Matrices
	{
	public:
		ColorMatrix^ BrightnessContrast(float brightness, float contrast)
		{
			float value = (float(0.5) * (float(1.0) - contrast)) + brightness;

			return gcnew ColorMatrix
			(
				gcnew array<array<float> ^>
				{
					gcnew array<float> {contrast, 0, 0, 0, 0},
					gcnew array<float> {0, contrast, 0, 0, 0},
					gcnew array<float> {0, 0, contrast, 0, 0},
					gcnew array<float> { 0, 0, 0, 1, 0 },
					gcnew array<float> {value, value, value, 2, 1},
				}
			);
		};

		static ColorMatrix^ Grayscale()
		{
			return gcnew ColorMatrix
				(
				gcnew array<array<float> ^>
			{
				gcnew array<float> {float(0.299), float(0.299), float(0.299), 0, 0},
					gcnew array<float> {float(0.587), float(0.587), float(0.587), 0, 0},
					gcnew array<float> {float(0.114), float(0.114), float(0.114), 0, 0},
					gcnew array<float> {0, 0, 0, 1, 0},
					gcnew array<float> {0, 0, 0, 0, 1},
			}
			);
		};

		static ColorMatrix^ Identity()
		{
			return gcnew ColorMatrix
				(
				gcnew array<array<float> ^>
			{
				gcnew array<float> {1, 0, 0, 0, 0},
					gcnew array<float> {0, 1, 0, 0, 0},
					gcnew array<float> {0, 0, 1, 0, 0},
					gcnew array<float> {0, 0, 0, 1, 0},
					gcnew array<float> {0, 0, 0, 0, 1},
			}
			);
		};

		static ColorMatrix^ Multiply(ColorMatrix^ matrix1, ColorMatrix^ matrix2)
		{
			if (matrix1 == nullptr || matrix2 == nullptr) return nullptr;
			ColorMatrix^ result = gcnew ColorMatrix();
			for (int x = 0; x < 5; x++)
			{
				for (int y = 0; y < 5; y++)
				{
					result[x, y] = 0;

					for (int z = 0; z < 5; z++)
					{
						result[x, y] += matrix1[x, z] * matrix2[z, y];
					}
				}
			}
			return result;
		};
	};

	class ImageToValues
	{

	public:
		static byte** Convert(Image^ image, Size^ outputSize, ColorMatrix^ matrix, Rectangle* section)
		{
			if (image == nullptr || matrix == nullptr)
			{
				return NULL;
			}

			byte** result;

			try
			{
				result = new byte*[outputSize->Height];

				for (int i = 0; i < outputSize->Height; i++)
				{
					result[i] = new byte[outputSize->Width];
				}
			}
			finally// (OutOfMemoryException)
			{
				//return null;
			}

			Rectangle targetSize = Rectangle(0, 0, outputSize->Width, outputSize->Height);

			{
				Bitmap^ resized = gcnew Bitmap(outputSize->Width, outputSize->Height);
				// draw a resized version onto the new bitmap
				{
					Graphics^ g = Graphics::FromImage(resized);

					g->InterpolationMode = InterpolationMode::HighQualityBicubic;

					g->DrawImage(
						image,
						targetSize,
						section->X,
						section->Y,
						section->Width,
						section->Height,
						GraphicsUnit::Pixel);
				}

				// copy the resized version onto a new bitmap, applying the matrix
				{
					Bitmap^ target = gcnew Bitmap(outputSize->Width, outputSize->Height);
					// create the image attributes and pass it the matrix
					{
						ImageAttributes^ imageAttributes = gcnew ImageAttributes();
						// merge the passed matrix with the matrix for converting to greyscale
						ColorMatrix^ matrices = Matrices::Multiply(Matrices::Grayscale(), matrix);

						imageAttributes->SetColorMatrix(matrices);

						{
							Graphics^ graphics = Graphics::FromImage(target);
							graphics->DrawImage(
								resized,
								targetSize,
								0,
								0,
								outputSize->Width,
								outputSize->Height,
								GraphicsUnit::Pixel,
								imageAttributes);
						}
					}

					BitmapData^ data = target->LockBits(targetSize, ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
					int padding = data->Stride - (outputSize->Width * 3);

					{
						byte* pointer = (byte*)data->Scan0.ToPointer();

						for (int y = 0; y < outputSize->Height; y++)
						{
							for (int x = 0; x < outputSize->Width; x++)
							{
								result[y][x] = pointer[2];

								pointer += 3;
							}

							pointer += padding;
						}
					}

					target->UnlockBits(data);
				}
			}

			return result;
		}
		
		static byte** Convert(Image^ image, Size^ outputSize, ColorMatrix^ matrix)
		{
			if (image == nullptr || matrix == nullptr)
			{
				return NULL;
			}

			return Convert(image, outputSize, matrix, new Rectangle(0, 0, image->Width, image->Height));
		}

		static byte** Convert(Image^ image, Size^ outputSize)
		{
			if (image == nullptr)
			{
				return NULL;
			}

			return Convert(image, outputSize, Matrices::Identity());
		}
	};

	class ImageToColors
	{

	public:
		static Color** Convert(Image^ image, Size* outputSize, Rectangle* section, bool reducingColors)
		{
			Color** outputArray;

			// create the resized and cropped image
			
			{
				Bitmap^ resizedImage = gcnew Bitmap(outputSize->Width, outputSize->Height);

				
				{
					Graphics^ g = Graphics::FromImage(resizedImage);

					g->InterpolationMode = InterpolationMode::HighQualityBicubic;

					g->DrawImage(
						image,
						Rectangle(0, 0, outputSize->Width, outputSize->Height),
						section->X,
						section->Y,
						section->Width,
						section->Height,
						GraphicsUnit::Pixel);
				}

				if (reducingColors)
				{
					// File name for the temporary file
					String^ temporaryFilename = Path::GetTempFileName();

					// Save as a 256 color gif file
					resizedImage->Save(temporaryFilename, ImageFormat::Gif);

					// load into an image
					
					{
						Bitmap^ gifImage = gcnew Bitmap(Image::FromFile(temporaryFilename));
						outputArray = BuildOutputArray(outputSize, gifImage);
					}

					try
					{
						// remove the temporary file
						File::Delete(temporaryFilename);
					}
					finally
					{
					}
				}
				else
				{
					// Build the output array from the 24-bit image
					outputArray = BuildOutputArray(outputSize, resizedImage);
				}
			}

			return outputArray;
		}

		static Color** Convert(Image^ image, Size* outputSize, bool reduceColors)
		{
			if (image == nullptr)
			{
				return NULL;
			}

			return Convert(
				image,
				outputSize,
				new Rectangle(0, 0, image->Width, image->Height),
				reduceColors);
		}

		static Color** BuildOutputArray(Size* outputSize, Bitmap^ resizedImage)
		{
			Color** result;
			//array<array<Color> ^> ^ result;

			try
			{
				/*result = gcnew array<array<Color> ^>(outputSize->Height);
				for (int i = 0; i < outputSize->Height; i++)
				{
					result[i] = gcnew array<Color>(outputSize->Width);
				}*/
				result = new Color*[outputSize->Height];
				result[0] = (Color *)malloc(outputSize->Height*outputSize->Width*sizeof(Color));
				for (int i = 1; i < outputSize->Height; i++)
				{
					result[i] = result[i - 1] + outputSize->Width;
				}
			}
			finally//catch (System.OutOfMemoryException)
			{
				//return null;
			}

			BitmapData^ data = resizedImage->LockBits(Rectangle(0, 0, outputSize->Width, outputSize->Height), ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
			int padding = data->Stride - (outputSize->Width * 3);

			{
				byte* pointer = (byte*)data->Scan0.ToPointer();

				for (int y = 0; y < outputSize->Height; y++)
				{
					for (int x = 0; x < outputSize->Width; x++)
					{
						result[y][x] = Color::FromArgb(pointer[2], pointer[1], pointer[0]);

						pointer += 3;
					}

					pointer += padding;
				}
			}

			return result;
		}
	};

	class ValuesToText
	{
	public:
		static string Apply(byte** values, Size^ outputSize, string Ramp)
		{
			if (values == NULL)
			{
				return NULL;
			}

			char *valueCharacters = new char[256];

			float length = (float)(Ramp.length() - 1);

			for (int x = 0; x < 256; x++)
			{
				valueCharacters[x] = Ramp[(int)((((float)x / float(255.0)) * length) + float(0.5))];
			}

			int numberOfColumns = outputSize->Width;
			int numberOfRows = outputSize->Height;

			string result;

			for (int y = 0; y < numberOfRows; y++)
			{
				StringBuilder^ builder = gcnew StringBuilder();

				for (int x = 0; x < numberOfColumns; x++)
				{
					builder->Append(gcnew String(valueCharacters, values[y][x], 1));
				}

				result += SStringToSTLString(builder->ToString());
				result += "\n";
			}

			return result;
		}
	};
	
	class ConvertImage
	{
	};

	class ImgData
	{
	private:
		int Brightness, Contrast;
		bool Existing, Finished;
		gcroot<Bitmap ^> bmp;
		byte** values;
		long len;
		gcroot<Image ^> img, img0;
		gcroot<String ^> word;
	public:
		/*void Create(Image^ img)
		{
			this->Existing = 1;
			this->Finished = 0;
			this->img = img;
			this->img0 = new Bitmap(img);
			this->bmp = gcnew Bitmap(img);
		};*/
		void Create(String^ FName)
		{
			this->Existing = 1;
			this->Finished = 0;
			this->img0 = Image::FromFile(FName);
			this->img = Image::FromFile(FName);
			this->bmp = gcnew Bitmap(img);
		};
		ImgData()
		{
			this->Existing = 0;
			this->Finished = 0;
			this->len = 0;
		}
		Bitmap^ GetBmp()
		{
			return this->bmp;
		}
		Image^ GetImg()
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
			this->Finished = 1;
		}
		bool isReady()
		{
			return this->Existing;
		}
		bool isFinished()
		{
			return this->Finished;
		}
		bool ReSize(double Wr, double Hr)
		{
			int _W = int(this->GetW()*Wr);
			int _H = int(this->GetH()*Hr);
			if (this->GetW() < 1 || this->GetH() < 1 || _W < 1 || _H < 1)
			{
				return 0;
			}
			this->bmp = gcnew Bitmap(this->img0, _W, _H);
			this->img = bmp;
			return 1;
		}
		bool ConvertI2V(string mask)
		{
			if (this->GetW() < 1 || this->GetH() < 1 || mask.length() < 1)
			{
				return this->Finished = 0;
			}

			// convert the image into values
			this->values = ImageToValues::Convert(
				this->img,
				gcnew Size(this->GetW(), this->GetH()),
				Matrices::Identity(),
				new Rectangle(0, 0, this->GetW(), this->GetH())
				);

			/*if (!imgData.ValuesCreated)
			{
			imgData.textViewer.Clear();

			MessageBox.Show(
			Resource.GetString("Out of Memory, Could not convert the image"),
			Resource.GetString("Error"),
			MessageBoxButtons.OK,
			MessageBoxIcon.Error);

			return 0;
			}*/

			// convert the values into texts
			this->len = this->GetW()*this->GetH();
			int maxl = this->len + this->GetH() + 2;
			string Converted = ValuesToText::Apply(this->values, gcnew Size(this->GetW(), this->GetH()), mask);
			this->word = gcnew String(Converted.c_str());

			return this->Finished = 1;
		}
		String^ GetWord()
		{
			return this->word;
		}
		void Delete()
		{
			this->Existing = 0;
			this->Finished = 0;
			delete this->img;
			delete this->bmp;
			delete this->word;
			delete this->img0;
		};
		~ImgData()
		{
			this->Delete();
		}
	} *IData;

}