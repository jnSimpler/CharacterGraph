#pragma once
#pragma comment( lib, "gdi32.lib" )

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
#include <windows.h>
#include <wingdi.h>
#using <mscorlib.dll>
//#using <gdi32.dll>

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

	class FontFunctions
	{
	private:
		struct TextMetric
		{
			/// <summary>Specifies the height (ascent + descent) of characters</summary>
			int tmHeight;

			/// <summary>Specifies the ascent (units above the base line) of characters</summary>
			int tmAscent;

			/// <summary>Specifies the descent (units below the base line) of characters</summary>
			int tmDescent;

			/// <summary>Specifies the amount of leading (space) inside the bounds set by the tmHeight member</summary>
			int tmInternalLeading;

			/// <summary>Specifies the amount of extra leading (space) that the application adds between rows</summary>
			int tmExternalLeading;

			/// <summary>Specifies the average width of characters in the font</summary>
			int tmAveCharWidth;

			/// <summary>Specifies the width of the widest character in the font</summary>
			int tmMaxCharWidth;

			/// <summary>Specifies the weight of the font</summary>
			int tmWeight;

			/// <summary>Specifies the extra width per string that may be added to some synthesized fonts</summary>
			int tmOverhang;

			/// <summary>Specifies the horizontal aspect of the device for which the font was designed</summary>
			int tmDigitizedAspectX;

			/// <summary>Specifies the vertical aspect of the device for which the font was designed</summary>
			int tmDigitizedAspectY;

			/// <summary>Specifies the value of the first character defined in the font</summary>
			char tmFirstChar;

			/// <summary>Specifies the value of the last character defined in the font</summary>
			char tmLastChar;

			/// <summary>Specifies the value of the character to be substituted for characters not in the font</summary>
			char tmDefaultChar;

			/// <summary>Specifies the value of the character that will be used to define word breaks for text justification</summary>
			char tmBreakChar;

			/// <summary>Specifies an italic font if it is nonzero</summary>
			byte tmItalic;

			/// <summary>Specifies an underlined font if it is nonzero</summary>
			byte tmUnderlined;

			/// <summary>Specifies a strikeout font if it is nonzero</summary>
			byte tmStruckOut;

			/// <summary>Specifies information about the pitch, the technology, and the family of a physical font</summary>
			byte tmPitchAndFamily;

			/// <summary>Specifies the character set of the font</summary>
			byte tmCharSet;
		};
	public:
		static Size MeasureText(String^ text, Font^ font)
		{
			if (String::IsNullOrEmpty(text) || font == nullptr)
			{
				return Size::Empty;
			}

			{
				Bitmap^ bitmap = gcnew Bitmap(1, 1);
				return TextRenderer::MeasureText(
					Graphics::FromImage(bitmap),
					text,
					font,
					Size(1, 1),
					TextFormatFlags::NoPadding | TextFormatFlags::NoPrefix);
				
			}
		}

		/*static bool IsFixedPitch(Font^ font)
		{
			if (font == nullptr)
			{
				return 1;
			}

			bool result;

			IntPtr fnt = font->ToHfont();

			{
				Bitmap^ bmp = gcnew Bitmap(1, 1);
				{
					Graphics^ g = Graphics::FromImage(bmp);
					IntPtr hdc = g->GetHdc();

					// store the current font and set the new one
					IntPtr fntOld = SelectObject(hdc, fnt);

					TextMetric metric = new TextMetric();

					GetTextMetrics(hdc, ref metric);

					result = (metric.tmPitchAndFamily & TMPF_FIXED_PITCH) == 0;

					// restore the old font
					SelectObject(hdc, fntOld);

					g.ReleaseHdc(hdc);
				}
			}

			DeleteObject(fnt);

			return result;
		}*/

		/*static bool IsFixedWidth(Font font)
		{
			return IsFixedPitch(font);
		}*/
	};

	class Extension
	{
	public:
		static string ResetExt(int Index, string extension)
		{
			string ext;

			switch (Index)
			{
			case 1:
				if (extension != ".bmp" && extension != ".rle" && extension != ".dib") ext = ".bmp";
				break;
			case 2:
				if (extension != ".gif") ext = ".gif";
				break;
			case 3:
				if (extension != ".jpg" && extension != ".jpeg" && extension != ".jpe") ext = ".jpg";
				break;
			case 4:
				if (extension != ".png") ext = ".png";
				break;
			case 5:
				if (extension != ".tif") ext = ".tif";
				break;
			}

			return ext;
		}

		//return the extension name with lower letters
		static string GetExt(String^ FileName)
		{
			return SStringToSTLString(Path::GetExtension(FileName)->ToLower());
		}
	};

	class Filter
	{
	public:
		//generate an array of Strings to fill the filter of savefiledialog
		static array<String ^> ^ SaveTypeFilter()
		{
			return gcnew array<String ^>(
			{
				L"All Files" + " (*.*)|*.*",
				L"Bitmap Images" + " (*.bmp, *.rle, *.dib)|*.bmp;*.rle;*.dib|",
				L"GIF Images" + " (*.gif)|*.gif|",
				L"JPEG Images" + " (*.jpg, *.jpeg, *.jpe)|*.jpg;*.jpeg;*.jpg|",
				L"Portable Network Graphics Images" + " (*.png)|*.png|",
				L"TIF Images" + " (*.tif, *.tiff)|*.tif;*.tiff|",
			}
			);
		}

		//generate selected Strings to fill the filter of savefiledialog
		static String ^ SelectSaveTypeFilter(int Index)
		{
			array<String ^> ^ Strings = SaveTypeFilter();
			return gcnew String(Strings[Index] + Strings[0]);
		}
	};

	class ImageFunctions
	{
	public:
		//Convert Extension string to ImageFormat
		static ImageFormat^ GetImageFormat(string extension)
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

		//Convert Extension string to ImageFormatID
		static int GetImageFormatIndex(string extension)
		{
			int index;

			switch (extension[1])
			{
			case 'p':
				index = 4;
				break;
			case 'j':
				index = 3;
				break;
			case 'g':
				index = 2;
				break;
			case 't':
				index = 5;
				break;
			default: // bmp, rle, dib
				index = 1;
				break;
			}

			return index;
		}

		//Convert Guid to String
		static String^ SetImageFormat(Guid guid)
		{
			String^ result;

			if (guid == ImageFormat::Png->Guid) result = ".png";
			else if (guid == ImageFormat::Jpeg->Guid) result = ".jpg";
			else if (guid == ImageFormat::Gif->Guid) result = ".gif";
			else if (guid == ImageFormat::Tiff->Guid) result = ".tif";
			else if (guid == ImageFormat::Bmp->Guid) result = ".bmp";

			return result;
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

	class TextToImage
	{
	private:
		static ColorMatrix^ Grayscale()
		{
			return gcnew ColorMatrix(
				gcnew array<array<float> ^>
			{
				gcnew array<float> { float(0.299), float(0.299), float(0.299), float(0), float(0) },
					gcnew array<float> { float(0.587), float(0.587), float(0.587), float(0), float(0) },
					gcnew array<float> { float(0.114), float(0.114), float(0.114), float(0), float(0) },
					gcnew array<float> { float(0), float(0), float(0), float(1), float(0) },
					gcnew array<float> { float(0), float(0), float(0), float(0), float(1) }
			}
			);
		}
	public:
		static Bitmap^ Convert(String^ text, Font^ font, Color textColor, Color backgroundColor, Point offset)
		{
			Size size = FontFunctions::MeasureText(text, font);

			Bitmap^ result = gcnew Bitmap(size.Width, size.Height);

			{
				Graphics^ graphics = Graphics::FromImage(result);
				graphics->Clear(backgroundColor);
				IDeviceContext^ g = graphics;
				TextRenderer::DrawText(
					g,
					text,
					font,
					offset,
					textColor,
					backgroundColor,
					TextFormatFlags::NoPadding | TextFormatFlags::NoPrefix);
			}

			return result;
		}

		static Bitmap^ Convert(String^ text, Font^ font, Color textColor, Color backgroundColor)
		{
			return Convert(text, font, textColor, backgroundColor, Point(0, 0));
		}

		static Bitmap^ Convert(String^ text, Font^ font)
		{
			return Convert(text, font, Color::Black, Color::White);
		}
	};

	class TextToColorImage
	{
	public:
		/*static Image^ Convert(String^ text, Font^ font, Color** textColors, Color backgroundColor, float scale)
		{
			if (!FontFunctions::IsFixedWidth(font) || text == null || textColors == null)
			{
				return null;
			}

			// size the output image must be to fit the text
			Size size = FontFunctions.MeasureText(FontFunctions.StringArrayToString(text), font);

			// size of one character in the font
			Size characterSize = FontFunctions.GetFixedPitchFontSize(font);

			Bitmap fullSize = new Bitmap(size.Width, size.Height);

			using (Graphics g = Graphics.FromImage(fullSize))
			{
				g.Clear(backgroundColor);

				int width = textColors[0].Length;
				int height = textColors.Length;

				for (int y = 0; y < height; y++)
				{
					string line = text[y];

					for (int x = 0; x < width; x++)
					{
						if (textColors[y][x] == backgroundColor)
						{
							continue;
						}

						Point offset = new Point(x * characterSize.Width, y * characterSize.Height);

						using (SolidBrush brush = new SolidBrush(textColors[y][x]))
						{
							g.DrawString(
								line[x].ToString(),
								font,
								brush,
								offset,
								StringFormat.GenericTypographic);
						}
					}
				}
			}

			if (scale == float(100))
			{
				return fullSize;
			}

			float magnification = scale / float(100);

			Size newSize = new Size(
				(int)((fullSize.Width * magnification) + 0.5),
				(int)((fullSize.Height * magnification) + 0.5));

			newSize.Width = Math.Max(newSize.Width, 1);
			newSize.Height = Math.Max(newSize.Height, 1);

			Bitmap resized = new Bitmap(newSize.Width, newSize.Height);

			using (Graphics g = Graphics.FromImage(resized))
			{
				g.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBicubic;

				g.DrawImage(fullSize, new Rectangle(0, 0, newSize.Width, newSize.Height));
			}

			fullSize.Dispose();

			return resized;
		}*/
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
		gcroot<Image ^> img0;
		gcroot<String ^> word;
		gcroot<ImageFormat ^> imgfmt;
	public:
		gcroot<Image ^> img;
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
			this->imgfmt = ImageFunctions::GetImageFormat(Extension::GetExt(FName));
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
		ImageFormat^ GetImgFmt()
		{
			return this->imgfmt;
		}
		Guid GetGuid()
		{
			return this->img->RawFormat->Guid;
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
			string Converted = ValuesToText::Apply(this->values, gcnew Size(this->GetW(), this->GetH()), mask);
			this->word = gcnew String(Converted.c_str());

			return this->Finished = 1;
		}
		bool ConvertT2I(Font^ font)
		{
			return 1;
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