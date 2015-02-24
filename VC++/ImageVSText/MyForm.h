#pragma once

#include "ImageVSText.h"

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

		string SStringToSTLString(String^ str)
		{
			return (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(str);
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
	private: System::Windows::Forms::Button^  SaveButton;
	private: System::Windows::Forms::Button^  ProceedButton;
	private: System::Windows::Forms::PictureBox^  Box1;
	private: System::Windows::Forms::PictureBox^  Box2;
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
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->OpenButton = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->Box2 = (gcnew System::Windows::Forms::PictureBox());
			this->Box1 = (gcnew System::Windows::Forms::PictureBox());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->ProceedButton = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Box2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Box1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
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
			this->panel1->Controls->Add(this->Box2);
			this->panel1->Controls->Add(this->Box1);
			this->panel1->Controls->Add(this->SaveButton);
			this->panel1->Controls->Add(this->ProceedButton);
			this->panel1->Controls->Add(this->OpenButton);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(529, 263);
			this->panel1->TabIndex = 1;
			// 
			// Box2
			// 
			this->Box2->Location = System::Drawing::Point(280, 32);
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
			// SaveButton
			// 
			this->SaveButton->Enabled = false;
			this->SaveButton->Location = System::Drawing::Point(165, 3);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(75, 23);
			this->SaveButton->TabIndex = 2;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
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
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(529, 263);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"Demo of function";
			this->panel1->ResumeLayout(false);
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
					 IData.Create(openFileDialog->FileName);
					 double r1 = IData.GetW() / double(IData.GetH()), r2 = Box1->Width / double(Box1->Height);
					 int W, H;
					 if (r1 > r2)
					 {
						 W = Box1->Width; H = int(W / r1);
					 }
					 else
					 {
						 H = Box1->Height; W = int(H * r1);
					 }
					 Bitmap^ image = gcnew Bitmap(IData.GetData(), W, H); //resize image
					 Box1->Image = image;
				 }
	}
private: System::Void ProceedButton_Click(System::Object^  sender, System::EventArgs^  e) {

}
};
}
