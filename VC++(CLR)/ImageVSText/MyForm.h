#pragma once

#include "ImageVSText.h"

using namespace ImgDataTech;

namespace ImageVSText {

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	protected:

	private: System::Windows::Forms::Button^  OpenButton;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  SaveTextButton;

	private: System::Windows::Forms::Button^  ProceedButton;
	private: System::Windows::Forms::PictureBox^  Box1;
	private: System::Windows::Forms::PictureBox^  Box2;
	private: System::Windows::Forms::RichTextBox^  TextBox;
	private: System::Windows::Forms::TextBox^  maskBox;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  RBoxH;



	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  RBoxW;
	private: System::Windows::Forms::Button^  SaveImgbutton;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialogText;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialogImage;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->OpenButton = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SaveImgbutton = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->RBoxW = (gcnew System::Windows::Forms::TextBox());
			this->RBoxH = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->maskBox = (gcnew System::Windows::Forms::TextBox());
			this->TextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->Box2 = (gcnew System::Windows::Forms::PictureBox());
			this->Box1 = (gcnew System::Windows::Forms::PictureBox());
			this->SaveTextButton = (gcnew System::Windows::Forms::Button());
			this->ProceedButton = (gcnew System::Windows::Forms::Button());
			this->saveFileDialogText = (gcnew System::Windows::Forms::SaveFileDialog());
			this->saveFileDialogImage = (gcnew System::Windows::Forms::SaveFileDialog());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Box2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Box1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
			this->openFileDialog->Filter = resources->GetString(L"openFileDialog.Filter");
			this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
			// 
			// OpenButton
			// 
			this->OpenButton->Location = System::Drawing::Point(3, 3);
			this->OpenButton->Name = L"OpenButton";
			this->OpenButton->Size = System::Drawing::Size(75, 23);
			this->OpenButton->TabIndex = 0;
			this->OpenButton->Text = L"Open";
			this->OpenButton->UseVisualStyleBackColor = true;
			this->OpenButton->Click += gcnew System::EventHandler(this, &MyForm::OpenButton_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->SaveImgbutton);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->RBoxW);
			this->panel1->Controls->Add(this->RBoxH);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->numericUpDown2);
			this->panel1->Controls->Add(this->numericUpDown1);
			this->panel1->Controls->Add(this->trackBar2);
			this->panel1->Controls->Add(this->trackBar1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->maskBox);
			this->panel1->Controls->Add(this->TextBox);
			this->panel1->Controls->Add(this->Box2);
			this->panel1->Controls->Add(this->Box1);
			this->panel1->Controls->Add(this->SaveTextButton);
			this->panel1->Controls->Add(this->ProceedButton);
			this->panel1->Controls->Add(this->OpenButton);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(761, 294);
			this->panel1->TabIndex = 1;
			// 
			// SaveImgbutton
			// 
			this->SaveImgbutton->Location = System::Drawing::Point(246, 3);
			this->SaveImgbutton->Name = L"SaveImgbutton";
			this->SaveImgbutton->Size = System::Drawing::Size(75, 23);
			this->SaveImgbutton->TabIndex = 18;
			this->SaveImgbutton->Text = L"SaveImage";
			this->SaveImgbutton->UseVisualStyleBackColor = true;
			this->SaveImgbutton->Click += gcnew System::EventHandler(this, &MyForm::SaveImgbutton_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(726, 8);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(11, 12);
			this->label5->TabIndex = 17;
			this->label5->Text = L"X";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(638, 8);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 12);
			this->label3->TabIndex = 16;
			this->label3->Text = L"X; H";
			// 
			// RBoxW
			// 
			this->RBoxW->Location = System::Drawing::Point(585, 5);
			this->RBoxW->Name = L"RBoxW";
			this->RBoxW->Size = System::Drawing::Size(47, 21);
			this->RBoxW->TabIndex = 15;
			this->RBoxW->Text = L"0.7";
			// 
			// RBoxH
			// 
			this->RBoxH->Location = System::Drawing::Point(673, 5);
			this->RBoxH->Name = L"RBoxH";
			this->RBoxH->Size = System::Drawing::Size(47, 21);
			this->RBoxH->TabIndex = 14;
			this->RBoxH->Text = L"0.336";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(521, 8);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(65, 12);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Resize:  W";
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Enabled = false;
			this->numericUpDown2->Location = System::Drawing::Point(395, 269);
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(59, 21);
			this->numericUpDown2->TabIndex = 10;
			this->numericUpDown2->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown2_ValueChanged);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Enabled = false;
			this->numericUpDown1->Location = System::Drawing::Point(5, 269);
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(69, 21);
			this->numericUpDown1->TabIndex = 9;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// trackBar2
			// 
			this->trackBar2->Enabled = false;
			this->trackBar2->LargeChange = 10;
			this->trackBar2->Location = System::Drawing::Point(460, 257);
			this->trackBar2->Maximum = 100;
			this->trackBar2->Minimum = -100;
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(298, 45);
			this->trackBar2->TabIndex = 8;
			this->trackBar2->ValueChanged += gcnew System::EventHandler(this, &MyForm::trackBar2_ValueChanged);
			// 
			// trackBar1
			// 
			this->trackBar1->Enabled = false;
			this->trackBar1->Location = System::Drawing::Point(80, 257);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Minimum = -100;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(309, 45);
			this->trackBar1->TabIndex = 7;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &MyForm::trackBar1_ValueChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(395, 254);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(59, 12);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Contrast:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 254);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(71, 12);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Brightness:";
			// 
			// maskBox
			// 
			this->maskBox->Location = System::Drawing::Point(327, 5);
			this->maskBox->Name = L"maskBox";
			this->maskBox->Size = System::Drawing::Size(188, 21);
			this->maskBox->TabIndex = 5;
			this->maskBox->Text = L"MMMMMMM@@@@@@@WWWWWWWWWBBBBBBBB000000008888888ZZZZZZZZZaZaaaaaa2222222SSSSSSSXXXX"
				L"XXXXXXX7777777rrrrrrr;;;;;;;;iiiiiiiii:::::::,:,,,,,,.........       ";
			// 
			// TextBox
			// 
			this->TextBox->Font = (gcnew System::Drawing::Font(L"SimSun", 6, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->TextBox->Location = System::Drawing::Point(246, 32);
			this->TextBox->Name = L"TextBox";
			this->TextBox->Size = System::Drawing::Size(269, 219);
			this->TextBox->TabIndex = 4;
			this->TextBox->Text = L"";
			this->TextBox->WordWrap = false;
			// 
			// Box2
			// 
			this->Box2->Location = System::Drawing::Point(521, 32);
			this->Box2->Name = L"Box2";
			this->Box2->Size = System::Drawing::Size(237, 219);
			this->Box2->TabIndex = 3;
			this->Box2->TabStop = false;
			// 
			// Box1
			// 
			this->Box1->Location = System::Drawing::Point(3, 32);
			this->Box1->Name = L"Box1";
			this->Box1->Size = System::Drawing::Size(237, 219);
			this->Box1->TabIndex = 2;
			this->Box1->TabStop = false;
			// 
			// SaveTextButton
			// 
			this->SaveTextButton->Location = System::Drawing::Point(165, 3);
			this->SaveTextButton->Name = L"SaveTextButton";
			this->SaveTextButton->Size = System::Drawing::Size(75, 23);
			this->SaveTextButton->TabIndex = 2;
			this->SaveTextButton->Text = L"SaveText";
			this->SaveTextButton->UseVisualStyleBackColor = true;
			this->SaveTextButton->Click += gcnew System::EventHandler(this, &MyForm::SaveTextButton_Click);
			// 
			// ProceedButton
			// 
			this->ProceedButton->Location = System::Drawing::Point(84, 3);
			this->ProceedButton->Name = L"ProceedButton";
			this->ProceedButton->Size = System::Drawing::Size(75, 23);
			this->ProceedButton->TabIndex = 1;
			this->ProceedButton->Text = L"Proceed";
			this->ProceedButton->UseVisualStyleBackColor = true;
			this->ProceedButton->Click += gcnew System::EventHandler(this, &MyForm::ProceedButton_Click);
			// 
			// saveFileDialogText
			// 
			this->saveFileDialogText->Filter = L"Plain Text (*.txt)|*.txt|All Files (*.*)|*.*";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(761, 294);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"Demo of function";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MyForm::MyForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Box2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Box1))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	}
	private: System::Void OpenButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 IData->Create(openFileDialog->FileName);
					 double r1 = IData->GetW() / double(IData->GetH()), r2 = Box1->Width / double(Box1->Height);
					 int W, H;
					 if (r1 > r2)
					 {
						 W = Box1->Width; H = int(W / r1);
					 }
					 else
					 {
						 H = Box1->Height; W = int(H * r1);
					 }
					 Bitmap^ image = gcnew Bitmap(IData->GetBmp(), W, H); //resize image
					 Box1->Image = image;
				 }
	}
private: System::Void ProceedButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (IData->isReady())
			 {
				 IData->ReSize(Convert::ToDouble(RBoxW->Text), Convert::ToDouble(RBoxH->Text));
				 try
				 {
					 if (IData->ConvertI2V(SStringToSTLString(maskBox->Text)))
					 {
						 TextBox->Text = IData->GetWord();
					 }
					 else
					 {
						 TextBox->Text = L"Failed";
					 }
				 }
				 finally
				 {

				 };
			 }

			 if (IData->isFinished())
			 {
				 try
				 {
					 IData->img = TextToImage::Convert(TextBox->Text, TextBox->Font);

					 double r1 = IData->GetW() / double(IData->GetH()), r2 = Box2->Width / double(Box2->Height);
					 int W, H;
					 if (r1 > r2)
					 {
						 W = Box2->Width; H = int(W / r1);
					 }
					 else
					 {
						 H = Box2->Height; W = int(H * r1);
					 }

					 Bitmap^ bmp = gcnew Bitmap(IData->GetImg(), W, H);
					 Box2->Image = bmp;
				 }
				 finally
				 {
				 }
			 }
}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
			 IData = new ImgData();
}
private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 
}
private: System::Void MyForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			 delete IData;
}
private: System::Void trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 numericUpDown1->Value = trackBar1->Value;
}
private: System::Void trackBar2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 numericUpDown2->Value = trackBar2->Value;
}
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 trackBar1->Value = Decimal::ToInt32(numericUpDown1->Value);
}
private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 trackBar2->Value = Decimal::ToInt32(numericUpDown2->Value);
}
private: System::Void SaveTextButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (saveFileDialogText->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 String^ ext = "";
				 if (Extension::GetExt(saveFileDialogText->FileName) != ".txt") ext = ".txt";
				 TextBox->SaveFile(saveFileDialogText->FileName + ext, RichTextBoxStreamType::PlainText);
			 }
}
private: System::Void SaveImgbutton_Click(System::Object^  sender, System::EventArgs^  e) {
			 string extension = Extension::GetExt(openFileDialog->FileName);
			 int id = ImageFunctions::GetImageFormatIndex(extension);
			 saveFileDialogImage->Filter = Filter::SelectSaveTypeFilter(id);
			 if (saveFileDialogImage->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 String ^ext = gcnew String(Extension::ResetExt(id, extension).c_str());

				 IData->GetImg()->Save(saveFileDialogImage->FileName + ext, IData->GetImgFmt());
			 }
}
};
}
