#pragma once
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>



namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
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
			int main(int);
			
			
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
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::Button^  button3;

	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::RichTextBox^  richTextBox2;
	private: System::Windows::Forms::Button^  button4;


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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.875F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(25, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(469, 42);
			this->label1->TabIndex = 0;
			this->label1->Text = L"EEP P13 Crisis Intelligency";
			// 
			// button1
			// 
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(32, 99);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(225, 245);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Record from AudioStream, Save to audio file";
			this->button1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(303, 99);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(1000, 100);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"I am ready!";
			// 
			// button2
			// 
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(34, 371);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(223, 244);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Audio File Input, Transcript and Display";
			this->button2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button2->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.Image")));
			this->button3->Location = System::Drawing::Point(34, 642);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(223, 201);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Stop Recording";
			this->button3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button3->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(-43, -88);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(100, 96);
			this->richTextBox1->TabIndex = 8;
			this->richTextBox1->Text = L"";
			// 
			// richTextBox2
			// 
			this->richTextBox2->Location = System::Drawing::Point(303, 221);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(1000, 717);
			this->richTextBox2->TabIndex = 9;
			this->richTextBox2->Text = L"";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(1140, 22);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(163, 51);
			this->button4->TabIndex = 10;
			this->button4->Text = L"EXIT";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1338, 985);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"Crisis Intelligency";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^ in = "HELLO, I am Crisis Intelligency\r\n";
		String ^ in2 = "Pretend Start recording...??? (Pending Don/Andy's coding)\r\n";
		String ^ in3 = "Pretend saving audio to a file...??? FileName:";
		textBox1->Text = in;
		textBox1->Text = textBox1->Text + in2;
		
		time_t now = time(0);
		struct tm tstruct;
		char buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d-%X", &tstruct);

		String ^ wavFileName = "Audio_Output_" + gcnew String(buf) + ".wav";

		//using namespace System::IO;
		//StreamWriter^ sw = gcnew StreamWriter(wavFileName);
		//sw->WriteLine(textBox1->Text);
		//sw->Close();

		textBox1->Text = textBox1->Text + in3 + wavFileName;


//		int res = system("/EEP-P13/IM-Proj/python translator.py");
	//	if (res != 0) {
		//	textBox1->Text = textBox1->Text + in2;

		//}

	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	
	using namespace std;
	using namespace System::IO;

	String ^ err2 = "Error in reading transcript file to display!";

	String ^ in4 = "Pretend opening wav file and then run Python program to do transcription...??? (Pending Andy's coding)\r\n";
	textBox1->Text = in4;
	
	


	//Call Python program and return Python Object
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
	String ^ returnFileName;

	//Initialize the Python Interpreter
	Py_Initialize();

	//Build the name object
	char* pyFileName2 = "read_n_display";
	//textBox1->Text = gcnew String(pyFileName2);
	pName = PyUnicode_FromString(pyFileName2);

	//Load the module object
	pModule = PyImport_Import(pName);
	if (pModule)
	{
		//textBox1->Text = textBox1->Text + "\r\npModule well imported";
	}
	else {
		textBox1->Text = textBox1->Text + "ERROR: pModule not imported";
		//exit(1);
	}


	//pDict is a borrowed reference
	//PyObject *err = PyDict_GetItemString(PyModule_GetDict(pModule), "SpecialisedError");
	//if (err) {
	//	PyErr_Format(err, "One %d two %d three %d.", 1, 2, 3);
	//}
	//else {
	//	PyErr_SetString(PyExc_RuntimeError, "Can not find exception in module");
	//}

	//if (pDict == nullptr)
	//{
	//	PyErr_Print();
	//	textBox1->Text = textBox1->Text + "null pDict";
	//	//exit(1);
	//}

	//pFunc is also a borrowed reference
	pFunc = PyObject_GetAttrString(pModule, "getFileName");
	if (pFunc && PyCallable_Check(pFunc))
	{
		//textBox1->Text = textBox1->Text + "\r\npFunc well ready";
		pValue = PyObject_CallObject(pFunc, NULL);
		if (pValue) {
			//textBox1->Text = textBox1->Text + "\r\nValue well returned";
			//textBox1->Text = textBox1->Text + " " + PyLong_AsLong(pValue);
			String ^ in5 = "Python write transcripts to a file and return filename: ";
			textBox1->Text = textBox1->Text + in5;

			returnFileName = gcnew String(PyUnicode_AsUnicode(pValue));
			textBox1->Text = textBox1->Text + returnFileName + "\r\n";

		}
		//PyUnicode_FromString(pValue);
		//PyBytes_AsString(pValue);
	}
	else {
		textBox1->Text = textBox1->Text + "ERROR: pFunc not ready";
		//exit(1);
	}
	//pFunc = PyDict_GeItemString(pDict, NULL);

	Py_DECREF(pModule);
	Py_DECREF(pName);

	Py_Finalize();



	//C++ OPEN IO and DISPLAY

	//System call
	//int res = system("/EEP-P13/IM-Proj/python read_n_display.py");
	//if (res != 0) {
	//	textBox1->Text = err2;
	//	cout << res;
	//}

	//System call with command line
	//string pyFileName = "/EEP-P13/IM-Proj/read_n_display.py";
	//string pyCommand = "python ";
	//pyCommand += pyFileName;
	//system(pyCommand.c_str());

	String ^ in6 = "C++ to open the file and display, filename: ";
	textBox1->Text = textBox1->Text + in6 + returnFileName;
	
	//String ^ tranFileName = "/EEP-P13/IM-Proj/Sample_transcript.txt";
	StreamReader^ sr = gcnew StreamReader(returnFileName);
	String ^ tranStr;
	
	while ((tranStr = sr->ReadLine()) != nullptr)
	{
		richTextBox2->AppendText(tranStr +"\n");
	};
	sr->Close();

	//StreamWriter^ sw = gcnew StreamWriter(tranFileName);
	//sw->WriteLine(textBox1->Text);
	//sw->Close();


}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	textBox1->Text = "Stop is pressed.  Thank you!";
}



private: System::Void button1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	exit(0);
}
};
}
