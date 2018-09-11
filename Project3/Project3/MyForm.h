#pragma once
#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <msclr/marshal_cppstd.h>
#include <Windows.h>

namespace Project3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::IO;

	bool thread1_run = true;
	bool thread2_run = true;
	bool thread3_run = true;
	bool thread4_run = true;
	bool thread5_run = true;
	bool main_thread_run = true;
	bool trans_update = true;
	int lastWordIdx = 0;
	bool trans_printed = false;
	
	ref struct MyGlobals {
		static String ^ StartTimestamp;
		static String ^ wavFolderName;
		static String ^ transFolderName;
		static String ^ transFileName;
		static String ^ folderParameter;
		static String ^ importFileName;
		static DateTime trans_update_dt;
		static String ^ RefNo;
		static 	PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
		//static System::Windows::Forms::RichTextBox ^ richTextBox2;
	};


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			thread1 = gcnew Thread(gcnew ThreadStart(this, &Project3::MyForm::recAndTrans));
			//thread2 = gcnew Thread(gcnew ThreadStart(this, &Project3::MyForm::checkUpdFile));
			thread4 = gcnew Thread(gcnew ThreadStart(this, &Project3::MyForm::transImport));
			//thread3 = gcnew Thread(gcnew ThreadStart(this, &Project3::MyForm::readDisplay));
			//backgroundWorker1 = gcnew System::ComponentModel::BackgroundWorker();
			//backgroundWorker1->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(backgroundWorker1_RunWorkerCompleted);

			InitializeComponent();
			button3->Enabled = false;
			button5->Enabled = false;
			textBox3->Enabled = false;
			button6->Enabled = false;
			button8->Enabled = false;


			button2->Visible = false;

			Image^ image1 = Image::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\record.png");
			button1->Image = image1;
			Image^ image3 = Image::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\stop.png");
			button3->Image = image3;
			Image^ image5 = Image::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\save.png");
			button5->Image = image5;
			Image^ image6 = Image::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\search.png");
			button6->Image = image6;
			Image^ image7 = Image::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\open.png");
			button7->Image = image7;
			Image^ image8 = Image::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\play.png");
			button8->Image = image8;


			//this->Width += 200;
			//this->Height += 200;
			this->richTextBox2->Width += 100;
			this->richTextBox2->Height += 100;

			//system("setup.cmd");



			//button3->Location = System::Drawing::Point(148, 90);
			//label2->Location = System::Drawing::Point(389, 93);
			//textBox2->Location = System::Drawing::Point(396, 139);
			
			//thread3_run = true;
			//thread3->Start();
			main();
			//
			//TODO: Add the constructor code here
			//
			//int main(int);

			
		}

	public:
		void AddReadDisplayMethod()
		{
			//			String^ myItem;
			//			for (int i = 1; i < 6; i++)
			//			{
						//	myItem = "MyListItem {0}", i;
							//richTextBox2->AppendText(myItem);
							//myListBox->Update();
			//}

			//Console::WriteLine("Expect to read file, " + MyGlobals::transFolderName + "Sample_transcript.txt");

			//DateTime transDt = File::GetLastWriteTime(MyGlobals::transFolderName);
			//Console::WriteLine("lastWriteTime - TRANS :" + transDt);


			//String ^transTest = "C:\\EEP-P13\\IM-Proj\\TEST\\Sample_transcript.txt";

			//String ^transTest = MyGlobals::transFolderName + "output_transcription.txt";
			
			try {
				FileStream^ fs = gcnew FileStream(MyGlobals::transFileName, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
				StreamReader^ sr = gcnew StreamReader(fs);
				String ^ tranStr;

				DateTime testDt = File::GetLastWriteTime(MyGlobals::transFileName);
				Console::WriteLine("We now reading, lastWriteTime - TEST, " + testDt + ", " + MyGlobals::transFileName);

				if (MyGlobals::trans_update_dt != testDt) {
					Console::WriteLine("old trans_update_dt ---" + MyGlobals::trans_update_dt);
					Console::WriteLine("new trans_update_dt ---" + testDt);

					MyGlobals::trans_update_dt = testDt;
					trans_update = true;
				}

				if (trans_update) {
					Console::WriteLine("File update_dt CHANGED!!!");
					richTextBox2->Text = "";

					while ((tranStr = sr->ReadLine()) != nullptr)
					{
						//char* tranChar = new char*(tranStr);
						//MyGlobals::richTextBox2->Text = "hello";
						richTextBox2->AppendText(tranStr + "\n");
						//richTextBox2->Text = tranStr + "\n";
						Console::WriteLine(tranStr);
						//richTextBox2->SendToBack();
						//backgroundWorker1->RunWorkerAsync();
						//if (richTextBox2->InvokeRequired) {
						//	StringArgReturningVoidDelegate^ d = gcnew StringArgReturningVoidDelegate(this, &Project3::MyForm::checkUpdFile);
						//	Invoke(d);
						//std::string name = "";
						//richTextBox2->Invoke(gcnew MethodInvoker(delegate{ name = richTextBox2->Text; }));
						//}
						//else
						//{
						//richTextBox2->Text = tranStr;
						//}
					};
					sr->Close();
					trans_update = false;
				}

			}
			catch (Exception ^ e)
			{
				Console::WriteLine("ERROR: Read trans file" + e);
			}

	
		}

	public:
		void ImportReadDisplayMethod()
		{
			//while (!trans_printed)
			//{
				try {
					FileStream^ fs = gcnew FileStream(MyGlobals::transFileName, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
					StreamReader^ sr = gcnew StreamReader(fs);
					String ^ tranStr;

					//DateTime testDt = File::GetLastWriteTime(MyGlobals::transFileName);
					Console::WriteLine("import file transcripts ---- " + MyGlobals::transFileName);

					/*if (MyGlobals::trans_update_dt != testDt) {
					Console::WriteLine("old trans_update_dt ---" + MyGlobals::trans_update_dt);
					Console::WriteLine("new trans_update_dt ---" + testDt);

					MyGlobals::trans_update_dt = testDt;
					trans_update = true;
					}*/

					//if (trans_update) {
					//	Console::WriteLine("File update_dt CHANGED!!!");
					richTextBox2->Text = "";

					while ((tranStr = sr->ReadLine()) != nullptr)
					{
						richTextBox2->AppendText(tranStr + "\n");
						Console::WriteLine(tranStr);
						trans_printed = true;
					};
					sr->Close();

				}
				catch (Exception ^ e)
				{
					Console::WriteLine("ERROR: Read trans file" + e);
				}

				if (trans_printed) {
					Console::WriteLine("Confirm trans_printed");
					richTextBox2->AppendText("<TRANSCRIPTION END>\n");
					thread4_run = false;
					thread5_run = false;
					button8->Enabled = false;
					if (MyGlobals::pModule) {
						Py_DECREF(MyGlobals::pModule);
					}
					if (MyGlobals::pName) {
						Py_DECREF(MyGlobals::pName);
					}

				}
			//}

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
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button6;
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::Button^  button8;


	private: Thread ^ thread1;
	//private: Thread ^ thread2;
	private: Thread ^ thread3;
	private: Thread ^ thread4;
	private: Thread ^ thread5;

	private: BackgroundWorker ^ backgroundWorker1;

	public: delegate void AddReadDisplay();
			AddReadDisplay^ myDelegate;
	public: delegate void ImportReadDisplay();
			ImportReadDisplay^ myDelegate2;
			 //delegate void StringArgReturningVoidDelegate(System::Windows::Forms::RichTextBox richTB);

//	private: Thread demoThread = null;

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
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
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
			this->label1->Text = L"EEP P13 Crisis Intelligence";
			// 
			// button1
			// 
			//this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			//this->button1->Image->FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\play.png");
			//	Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(32, 90);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 95);
			this->button1->TabIndex = 1;
			this->button1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(1049, 90);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(1450, 107);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"HELLO, I am Crisis Intelligence. I am ready!";
			// 
			// button2
			// 
			this->button2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button2.Image")));
			this->button2->Location = System::Drawing::Point(148, 90);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 95);
			this->button2->TabIndex = 3;
			this->button2->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button2->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button3.Image")));
			this->button3->Location = System::Drawing::Point(148, 90);
			//this->button3->Location = System::Drawing::Point(264, 90);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(95, 95);
			this->button3->TabIndex = 6;
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
			this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBox2->Location = System::Drawing::Point(34, 280);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->Size = System::Drawing::Size(1806, 1121);
			this->richTextBox2->TabIndex = 9;
			this->richTextBox2->Text = L"";
			this->richTextBox2->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox2_TextChanged);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(2350, 22);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(100, 50);
			this->button4->TabIndex = 10;
			this->button4->Text = L"EXIT";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->textBox2->Location = System::Drawing::Point(396, 139);
			this->textBox2->Location = System::Drawing::Point(264, 139);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(210, 44);
			this->textBox2->TabIndex = 11;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			//this->label2->Location = System::Drawing::Point(389, 93);
			this->label2->Location = System::Drawing::Point(264, 93);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(201, 37);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Reference No.";
			// 
			// button5
			// 
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button5->Location = System::Drawing::Point(802, 93);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(95, 95);
			this->button5->TabIndex = 13;
			//this->button5->Text = L"EXP";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(1400, 230);
			//this->textBox3->Location = System::Drawing::Point(849, 90);
			this->textBox3->Multiline = false;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = false;
			this->textBox3->Size = System::Drawing::Size(500, 44);
			this->textBox3->TabIndex = 14;
			this->textBox3->Text = L"Searching...";
			this->textBox3->Click += gcnew System::EventHandler(this, &MyForm::textBox3_Click);
			// 
			// button6
			// 
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button6->Location = System::Drawing::Point(1900, 229);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(55, 53);
			this->button6->TabIndex = 15;
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
			// 
			// button7
			// 
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->Location = System::Drawing::Point(562, 93);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(95, 95);
			this->button7->TabIndex = 16;
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// button8
			// 
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button8->Location = System::Drawing::Point(682, 93);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(95, 95);
			this->button8->TabIndex = 17;
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::button8_Click);
			// 
			// listView
			// 
			this->listView1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listView1->Name = L"listView1";
			this->listView1->TabIndex = 16;
			this->listView1->Bounds = System::Drawing::Rectangle(System::Drawing::Point(2100, 229), System::Drawing::Size(400, 1350));
			// Set the view to show details.
			listView1->View = System::Windows::Forms::View::Details;
			// Allow the user to edit item text.
			listView1->LabelEdit = true;
			// Allow the user to rearrange columns.
			listView1->AllowColumnReorder = false;
			// Display check boxes.
			listView1->CheckBoxes = false;
			// Select the item and subitems when selection is made.
			listView1->FullRowSelect = true;
			// Display grid lines.
			listView1->GridLines = true;
			listView1->Scrollable = false;
			listView1->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			// Sort the items in the list in ascending order.
			//listView1->Sorting = System::Windows::Forms::SortOrder::Ascending;
			listView1->Sorting = System::Windows::Forms::SortOrder::None;
			// Create three items and three sets of subitems for each item.
			ListViewItem ^ item1 = gcnew System::Windows::Forms::ListViewItem("HSBC");
			// Place a check mark next to the item.
			//item1->Checked = true;
			//item1->SubItems->Add("HSBC");
			ListViewItem ^ item2 = gcnew System::Windows::Forms::ListViewItem("RBWM");
			//item2->SubItems->Add("RBWM");
			ListViewItem ^ item3 = gcnew System::Windows::Forms::ListViewItem("CMB");
			ListViewItem ^ item4 = gcnew System::Windows::Forms::ListViewItem("<Add new word>");
			lastWordIdx = 3;
			// Place a check mark next to the item.
			//item3->Checked = true;
			//item3->SubItems->Add("CMB");
			// Create columns for the items and subitems.
			// Width of -2 indicates auto-size.
			this->listView1->Columns->Add("Custom Words", -2, System::Windows::Forms::HorizontalAlignment::Left);
			
			//Add the items to the ListView.
			array<ListViewItem^>^temp1 = { item1,item2,item3, item4 };
			this->listView1->Items->AddRange(temp1);
/*			// Create two ImageList objects.
			ImageList ^ imageListSmall = gcnew ImageList();
			ImageList ^ imageListLarge = gcnew ImageList();
			// Initialize the ImageList objects with bitmaps.
			imageListSmall->Images->Add(System::Drawing::Bitmap::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\stop.png"));
			imageListSmall->Images->Add(System::Drawing::Bitmap::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\play.png"));
			imageListLarge->Images->Add(System::Drawing::Bitmap::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\save.png"));
			imageListLarge->Images->Add(System::Drawing::Bitmap::FromFile("C:\\Users\\Wisy\\source\\repos\\Project3\\picture\\record.png"));
			//Assign the ImageList objects to the ListView.
			listView1->LargeImageList = imageListLarge;
			listView1->SmallImageList = imageListSmall;
*/
			this->listView1->OwnerDraw = true;
			this->listView1->DrawItem += gcnew System::Windows::Forms::DrawListViewItemEventHandler(this, &MyForm::listView1_DrawItem);
			this->listView1->DrawSubItem += gcnew System::Windows::Forms::DrawListViewSubItemEventHandler(this, &MyForm::listView1_DrawSubItem);
			this->listView1->DrawColumnHeader += gcnew System::Windows::Forms::DrawListViewColumnHeaderEventHandler(this, &MyForm::listView1_DrawColumnHeader);
				
			this->listView1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::listView1_MouseDown);
			this->listView1->AfterLabelEdit += gcnew System::Windows::Forms::LabelEditEventHandler(this, &MyForm::listView1_AfterLabelEdit);
			saveCustom_Word();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(1896, 1375);
			//this->Bounds = System::Drawing::Size(3000, 2000);
			//this->ClientSize = System::Drawing::Size(1896, 1375);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->listView1);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button8);
			this->Name = L"MyForm";
			this->Text = L"Crisis Intelligence";
			//this->Size = System::Drawing::Size(2000, 3000);
			this->ResumeLayout(false);
			this->PerformLayout();

			myDelegate = gcnew AddReadDisplay(this, &MyForm::AddReadDisplayMethod);

			myDelegate2 = gcnew ImportReadDisplay(this, &MyForm::ImportReadDisplayMethod);
		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		String ^ inTB2 = textBox2->Text;
		MyGlobals::RefNo = inTB2;
		
		if (String::IsNullOrEmpty(inTB2)) {
			textBox1->Text = "ERROR: Missing Reference No. input!";
		}
		else {
			button1->Enabled = false;
			button3->Enabled = true;
			textBox2->ReadOnly = true;
			button7->Enabled = false;
			button8->Enabled = false;

			time_t now = time(0);
			struct tm tstruct;
			char buf[80];
			tstruct = *localtime(&now);
			strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M-%S", &tstruct);
			MyGlobals::StartTimestamp = gcnew String(buf);
			//MyGlobals::wavFolderName = "C:\\EEP-P13\\IM-Proj\\TEST\\Audio_Output_Ref" + inTB2 + "_" + MyGlobals::StartTimestamp + "\\";
			//MyGlobals::transFolderName = "C:\\EEP-P13\\IM-Proj\\TEST\\Trans_Output_Ref" + inTB2 + "_" + MyGlobals::StartTimestamp + "\\";
			MyGlobals::wavFolderName = "C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Audio_Output_Ref" + inTB2 + "_" + MyGlobals::StartTimestamp + "\\";
			MyGlobals::transFolderName = "C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Trans_Output_Ref" + inTB2 + "_" + MyGlobals::StartTimestamp + "\\";
			MyGlobals::transFileName = MyGlobals::transFolderName + "output_transcription.txt";
			MyGlobals::folderParameter = "Ref" + inTB2 + "_" + MyGlobals::StartTimestamp;

			String ^ in = "Reference No.: " + inTB2 + "\r\n";
			String ^ in2 = "Record start.\r\n";
			String ^ in3 = "Audio Folder: " + MyGlobals::wavFolderName + "\r\n";
			String ^ in4 = "Transcripts Folder: " + MyGlobals::transFolderName + "\r\n";
			
			textBox1->Text = in + in2 + in3 + in4;

			using namespace System;
			using namespace System::IO;
			try {
				if (Directory::Exists(MyGlobals::wavFolderName)) {
					Console::WriteLine("WAV Directory already exists.");
				}
				else {
					DirectoryInfo ^ di = Directory::CreateDirectory(MyGlobals::wavFolderName);
				}

			}
			catch (Exception ^ e) {
				Console::WriteLine("Failed to create WAV directory " + MyGlobals::wavFolderName, e);
			}

			try {
				if (Directory::Exists(MyGlobals::transFolderName)) {
					Console::WriteLine("TRANS Directory already exists.");
				}
				else {
					DirectoryInfo ^ di = Directory::CreateDirectory(MyGlobals::transFolderName);
				}

			}
			catch (Exception ^ e) {
				Console::WriteLine("Failed to create TRANS directory " + MyGlobals::transFolderName, e);
			}

			//FileStream^ fs = gcnew FileStream(MyGlobals::transFileName, FileMode::Create);

			//using namespace System::IO;
			//StreamWriter^ sw = gcnew StreamWriter(wavFileName);
			//sw->WriteLine(textBox1->Text);
			//sw->Close();

			//Thread^ thread1 = gcnew Thread(gcnew ThreadStart(this, &Project3::MyForm::recAndTrans));
			thread1->Name = "recAndTransThread";
			thread1_run = true;
			thread1->Start();

			//Thread^ thread2 = gcnew Thread(gcnew ThreadStart(this, &Project3::MyForm::checkUpdFile));
			//thread2->Name = "checkUpdFileThread";
			//thread2_run = true;
			//thread2->Start();

			//int res = system("/EEP-P13/IM-Proj/python translator.py");
			//if (res != 0) {
			//	textBox1->Text = textBox1->Text + in2;

			//}
			thread3 = gcnew Thread(gcnew ThreadStart(this, &MyForm::ThreadFunction));
			thread3_run = true;
			thread3->Start();


			

		}

}

//private: System::Void setTextSafeBtn_Click(object sender, EventArgs e) {
//	this.demoThread = new Thread(new ThreadStart(this.ThreadProcSafe));
//	this.demoThread.Start();
//}

//private: System::Void ThreadProcSafe() {
//	this.setText("This text was set safely");
//}
//private: System::Void SetText(string text) {
//	if (this->richTextBox2.InvokeRequired) {
//		StringArgReturningVoidDelegrate d = new StringArgReturningVoidDelegate(SetText);
//		this.Invole(d, new object[]{ text });

//	}
//	else
//	{
//		this->richTextBox2.Text = text;
//	}
//}

			 //private: void setTextBackgroundWorkerBtn_Click(
				// System::Object sender,
			//	 EventArgs e)
			 //{
				// backgroundWorker1.RunWorkerAsync();
			 //}

			// private: void backgroundWorker1_RunWorkerCompleted(
				//		  System::Object sender,
					//	  RunWorkerCompletedEventArgs e)
					  //{
						//  richTextBox2->Text = "This text was set safely by BackgroundWorker.";
					  //}

private: void recAndTrans() {
	//for (;;) {

	/*
	char* pyAudioProgram = "python audiochunker.py 15";
	char* exitCommand = "exit()";
	//system("python");
	system("dir/w");
	system(pyAudioProgram);
	system("python audiochunkerR.py");
	*/


	
	//Call Python program and return Python Object
	//PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
	//String ^ returnFileName;
/*
	//Initialize the Python Interpreter
	Py_Initialize();

	//Build the name object
	char* pyFileName = "audiochunker";
	//char* pyFileName2 = "read_n_display";
	char* pyArg = "10";
	MyGlobals::pName = PyUnicode_FromString(pyFileName);
	//, pyArg);

	//Load the module object
	MyGlobals::pModule = PyImport_Import(MyGlobals::pName);
	if (MyGlobals::pModule)
	{
		Console::WriteLine("recAndTrans YES: pModule well imported");
	}
	else {
		Console::WriteLine("recAndTrans ERROR: pModule not imported");
		if (PyErr_Occurred()) {
			Console::WriteLine("ERROR - pModule");
			PyErr_Print();
		}
	}
	

	//pFunc is also a borrowed references
	MyGlobals::pFunc = PyObject_GetAttrString(MyGlobals::pModule, "getFileName");
	if (MyGlobals::pFunc && PyCallable_Check(MyGlobals::pFunc))
	{
		MyGlobals::pValue = PyObject_CallObject(MyGlobals::pFunc, NULL);
		if (MyGlobals::pValue) {
			String ^ in5 = "Python write transcripts to a file and return ";
			Console::WriteLine("Return ========= " + gcnew String(PyUnicode_AsUnicode(MyGlobals::pValue)));
			//returnFileName = gcnew String(PyUnicode_AsUnicode(pValue));
		}
	}
	else {
		Console::WriteLine("ERROR: pFunc not ready");
	}

	
	if (MyGlobals::pModule) {
		Py_DECREF(MyGlobals::pModule);
	}
	if (MyGlobals::pName) {
		Py_DECREF(MyGlobals::pName);
	}
	

	Py_Finalize();
	*/

	int listencount = 1;
	int sample = 44100;
	int chunksize = 20;
	//int chunksize = 15;
	//int chunksize = 60;
	int count = 0;
	String ^ commandString = "";
	std::string commandStr = "";
	const char* commandChar;

	count = chunksize - 5;
//	count = chunksize - 3;

	using namespace Runtime::InteropServices;

	while (thread1_run) {
		Console::WriteLine("Thread - recAndTrans - Loop for Python to record ===== Deadlistener \r\n" + listencount);
		
		commandString = "python -W ignore deadlistener_integration_test_hardcode.py " + MyGlobals::folderParameter + " " + listencount + " " + chunksize + " " + sample;
		commandChar = (const char*)(Marshal::StringToHGlobalAnsi(commandString)).ToPointer();
		commandStr = commandChar;
		Marshal::FreeHGlobal(IntPtr((void*)commandChar));
		
		system(commandStr.c_str());

		Console::WriteLine("python -W ignore deadlistener_integration_test_hardcode.py " + MyGlobals::folderParameter + " " + listencount + " " + chunksize + " " + sample);

		listencount += 1;

		Thread::Sleep(count*1000);
	}
}
//public: void checkUpdFile(System::Windows::Forms::RichTextBox richTB) {
/*private: void checkUpdFile() {

	//for (;;) {
	while (thread2_run) {
		printf("Thread - checkUpdFile - Loop for Python to transcript\r\n");
		Thread::Sleep(5000);
	}
	
}*/

private: void readDisplay() {
	//this->InitializeComponent();
	while(thread3_run) {
		printf("Thread - readDisplay\r\n");
		Thread::Sleep(5000);

	}
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	
	using namespace std;
	using namespace System::IO;

	String ^ err2 = "Error in reading transcript file to display!";

	String ^ in4 = "Read transcript & Display\r\n";
	textBox1->Text = in4;
	
	


	//Call Python program and return Python Object
	PyObject *pName, *pModule, *pDict, *pFunc, *pValue;
	String ^ returnFileName;

	//Initialize the Python Interpreter
	Py_Initialize();

	//Build the name object
	char* pyFileName2 = "read_n_display";
	//char* pyFileName2 = "transcribe_async_short_file";
	//textBox1->Text = gcnew String(pyFileName2);
	pName = PyUnicode_FromString(pyFileName2);

	//Load the module object
	pModule = PyImport_Import(pName);
	if (pModule)
	{
		//textBox1->Text = textBox1->Text + "\r\npModule well imported";
		Console::WriteLine("YES: Module well imported");
	}
	else {
		Console::WriteLine("ERROR: pModule not imported");
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

	//pFunc is also a borrowed references
	pFunc = PyObject_GetAttrString(pModule, "getFileName");
	if (pFunc && PyCallable_Check(pFunc))
	{
		//textBox1->Text = textBox1->Text + "\r\npFunc well ready";
		pValue = PyObject_CallObject(pFunc, NULL);
		if (pValue) {
			//textBox1->Text = textBox1->Text + "\r\nValue well returned";
			//textBox1->Text = textBox1->Text + " " + PyLong_AsLong(pValue);
			String ^ in5 = "Python write transcripts to a file and return filename: ";
			returnFileName = gcnew String(PyUnicode_AsUnicode(pValue));
			//textBox1->Text = textBox1->Text + in5 + returnFileName + "\r\n";

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
	//textBox1->Text = textBox1->Text + in6 + returnFileName;
	
	//String ^ tranFileName = "/EEP-P13/IM-Proj/Sample_transcript.txt";
	StreamReader^ sr = gcnew StreamReader(returnFileName);
	String ^ tranStr;
	
	while ((tranStr = sr->ReadLine()) != nullptr)
	{
		//MyGlobals::richTextBox2->AppendText(tranStr +"\n");
	};
	sr->Close();

	//StreamWriter^ sw = gcnew StreamWriter(tranFileName);
	//sw->WriteLine(textBox1->Text);
	//sw->Close();


}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	thread1_run = false;
	thread2_run = false;
	thread3_run = false;
	main_thread_run = false;
	textBox1->Text = "Stop is pressed.  Thank you!";
	button1->Enabled = false;
	button3->Enabled = false;
	button5->Enabled = true;
	textBox3->Enabled = true;
	button6->Enabled = true;

	if (MyGlobals::pModule) {
		Py_DECREF(MyGlobals::pModule);
	}
	if (MyGlobals::pName) {
		Py_DECREF(MyGlobals::pName);
	}


	//Py_Finalize();

}



private: System::Void button1_Enter(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	exit(0);
}

private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	/*OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog;

	openFileDialog1->InitialDirectory = "C:\\";
	openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
	openFileDialog1->FilterIndex = 2;
	openFileDialog1->RestoreDirectory = true;
	*/
	//if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//String saveFileName = openFileDialog1->GetSaveFileName();
		//Console::WriteLine("Open Dialogue to Save File!!");
	//}
	
		// Displays a SaveFileDialog so the user can save the Image  
		// assigned to Button2.  

	Console::WriteLine("Export button clicked");

	using namespace System::IO;
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
		saveFileDialog1->InitialDirectory = "C:\\Users\\Wisy\\Documents\\";
		saveFileDialog1->FileName = "Trans_Output_FULL" + "_IR" + MyGlobals::RefNo + "_" + MyGlobals::StartTimestamp + ".rtf";
		if (trans_printed) {
			saveFileDialog1->FileName = "Trans_Output_FULL" + "_IMPORT_" + MyGlobals::StartTimestamp + ".rtf";
		}
		saveFileDialog1->Filter = "RTF Files | *.rtf";	//"JPeg Image|*.jpg|Bitmap Image|*.bmp|Gif Image|*.gif";
		saveFileDialog1->Title = "Save Transcripts File";
		saveFileDialog1->FilterIndex = 2;
		saveFileDialog1->RestoreDirectory = true;

		StreamWriter^ writer;	// gcnew StreamWriter();

		if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//if ((writer = gcnew StreamWriter(saveFileDialog1->OpenFile())) != nullptr) {
				// If the file name is not an empty string open it for saving.  
				if (saveFileDialog1->FileName != "") {
					// Saves the Image via a FileStream created by the OpenFile method.  
					//FileStream^ fs = gcnew FileStream(saveFileDialog1->OpenFile(), FileMode::OpenOrCreate, FileAccess::Write, FileShare::Write);
					
					//String ^transTest = "C:\\EEP-P13\\IM-Proj\\TEST\\Sample_transcript.txt";
					//FileStream^ fs = gcnew FileStream(transTest, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
					//StreamReader^ sr = gcnew StreamReader(fs);
					//String ^ tranStr;
					//StreamWriter^ sw = gcnew StreamWriter(fs);
					//writer->WriteLine(richTextBox2->Text);
					richTextBox2->SaveFile(saveFileDialog1->FileName);
					// Saves the Image in the appropriate ImageFormat based upon the  
					// File type selected in the dialog box.  
					// NOTE that the FilterIndex property is one-based.  
					Console::WriteLine("save file");
					//fs->Close();
				}

				//writer->Dispose();
				//writer->Close();
			//}
		}

	


}

private: System::Void richTextBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	richTextBox2->SelectionStart = richTextBox2->Text->Length;
	richTextBox2->ScrollToCaret();
}
private: System::Void listView1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	//Console::WriteLine("listView1_MouseDown");
	ListViewItem ^selection = listView1->GetItemAt(e->X, e->Y);
	int index = selection->Index;
	//Console::WriteLine("selected: " + index + "," + selection->Text);
}
private: System::Void listView1_AfterLabelEdit(System::Object^ sender, System::Windows::Forms::LabelEditEventArgs^ e) {
	Console::WriteLine("after label edit, new label:" + e->Label + "/");
	String ^emptyStr = "";
	if (String::IsNullOrEmpty(e->Label)) {
		Console::WriteLine("eLabel:" + e->Label + "/");
		Console::WriteLine("Empty :" + emptyStr + "/");
		return;
	}
	int index = e->Item;
	System::Drawing::Rectangle ^rect = listView1->GetItemRect(index);
	Console::WriteLine("E rect: ," + rect->X + "-" + rect->Y);
	listView1->GetItemAt(rect->X, rect->Y)->Text = e->Label;
	ListViewItem ^ li = listView1->GetItemAt(rect->X, rect->Y);
	Console::WriteLine("E text: ," + index + "+" + li->Text);

	if (index == lastWordIdx && String::Compare(e->Label, "<Add new word>",StringComparison::OrdinalIgnoreCase) != 0 && lastWordIdx < 20) {
		Console::WriteLine("added new word:"+lastWordIdx);
		ListViewItem ^ itemN = gcnew System::Windows::Forms::ListViewItem("<Add new word>");
		itemN->SubItems->Add("<Add new word>");
		listView1->Items->Add(itemN);
		lastWordIdx += 1;
	}
	saveCustom_Word();
}
private: void saveCustom_Word() {
	Console::WriteLine("Save Custom Words");

	StreamWriter^ writer;
	try {
		writer = gcnew StreamWriter("C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\customWord.csv", false);
		for each(ListViewItem^ li in listView1->Items)
			writer->WriteLine(li->Text + ",");
		writer->Close();
	}
	catch (Exception ^ e) {
		Console::WriteLine("ERROR - write custom word ", e);
	}

}


private: System::Void listView1_DrawItem(System::Object^ sender, System::Windows::Forms::DrawListViewItemEventArgs^ e) {
	/*
	if ((int) (e->State & System::Windows::Forms::ListViewItemStates::Selected) !=  0) {
		e->Graphics->FillRectangle(Brushes::Maroon, e->Bounds);
		e->DrawFocusRectangle();
	}
	else {
		System::Drawing::Drawing2D::LinearGradientBrush^ brush = gcnew System::Drawing::Drawing2D::LinearGradientBrush(e->Bounds, Color::Orange, Color::Maroon, System::Drawing::Drawing2D::LinearGradientMode::Horizontal);
		e->Graphics->FillRectangle(brush, e->Bounds);
		
	}
	*/
	if (listView1->View != System::Windows::Forms::View::Details) {
		e->DrawText();
	}
	return;

}
private: System::Void listView1_DrawSubItem(System::Object^ sender, DrawListViewSubItemEventArgs^ e) {
	TextFormatFlags flags = TextFormatFlags::Left;
	System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();

/*			 using (StringFormat sf = new StringFormat())
			 {
				 // Store the column text alignment, letting it default
				 // to Left if it has not been set to Center or Right.
				 switch (e.Header.TextAlign)
				 {
				 case HorizontalAlignment.Center:
					 sf.Alignment = StringAlignment.Center;
					 flags = TextFormatFlags.HorizontalCenter;
					 break;
				 case HorizontalAlignment.Right:
					 sf.Alignment = StringAlignment.Far;
					 flags = TextFormatFlags.Right;
					 break;
				 }
*/
		// Draw the text and background for a subitem with a 
		// negative value. 
		double subItemValue;
		if (e->ColumnIndex > 0 && Double::TryParse(e->SubItem->Text, System::Globalization::NumberStyles::Currency, System::Globalization::NumberFormatInfo::CurrentInfo, subItemValue) && subItemValue < 0)
		{
			// Unless the item is selected, draw the standard 
			// background to make it stand out from the gradient.
			if ((int) (e->ItemState & System::Windows::Forms::ListViewItemStates::Selected) == 0)
			{
				e->DrawBackground();
			}

			// Draw the subitem text in red to highlight it. 
			e->Graphics->DrawString(e->SubItem->Text, listView1->Font, Brushes::Red, e->Bounds, sf);

			return;
		}

		// Draw normal text for a subitem with a nonnegative 
		// or nonnumerical value.
		e->DrawText(flags);
		//}
}

private: System::Void listView1_DrawColumnHeader(System::Object^ sender, System::Windows::Forms::DrawListViewColumnHeaderEventArgs^ e) {
	
	
	System::Drawing::StringFormat^ sf = gcnew System::Drawing::StringFormat();
	System::Drawing::Font^ headerfont = gcnew System::Drawing::Font("Helvetica", 14, System::Drawing::FontStyle::Bold);

	e->DrawBackground();

	e->Graphics->DrawString(e->Header->Text, headerfont, Brushes::Black, e->Bounds, sf);
	
	return;
	
}

private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		Console::WriteLine("Searching button clicked");

		int start = 0;
		int end = richTextBox2->Text->LastIndexOf(textBox3->Text);

		richTextBox2->SelectAll();
		richTextBox2->SelectionBackColor = Color::White;

		while (start < end)
		{
			richTextBox2->Find(textBox3->Text, start, richTextBox2->TextLength, RichTextBoxFinds::MatchCase);
			richTextBox2->SelectionBackColor = Color::Yellow;

			start = richTextBox2->Text->IndexOf(textBox3->Text, start) + 1;
		}
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
	Console::WriteLine("open clicked");

	// Displays an OpenFileDialog so the user can select a Cursor.  
	OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->InitialDirectory = "C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\";
	openFileDialog1->Filter = "WAV Files|*.wav";
	openFileDialog1->RestoreDirectory == true;
	openFileDialog1->Title = "Select an Audio WAV File";

	// Show the Dialog.  
	// If the user clicked OK in the dialog and  
	// a .CUR file was selected, open it.  
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String ^ inputFileName = openFileDialog1->FileName;
		textBox1->Text = "Import File: " + inputFileName;
		MyGlobals::importFileName = inputFileName;
		button1->Enabled = false;
		button3->Enabled = false;
		button8->Enabled = true;
	}
}
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
	Console::WriteLine("play clicked");
	button7->Enabled = false;
	button5->Enabled = true;
	textBox2->ReadOnly = true;
	textBox3->Enabled = true;
	button6->Enabled = true;


	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d-%H-%M-%S", &tstruct);
	MyGlobals::StartTimestamp = gcnew String(buf);
	MyGlobals::transFolderName = "C:\\Users\\Wisy\\source\\repos\\Project3\\Project3\\Trans_Output_IMPORT_" + MyGlobals::StartTimestamp + "\\";
	MyGlobals::transFileName = MyGlobals::transFolderName + "output_transcription.txt";
	MyGlobals::folderParameter = "IMPORT_" + MyGlobals::StartTimestamp;

	String ^ in = "Import File: " + MyGlobals::importFileName + "\r\n";
	String ^ in4 = "Transcripts Folder: " + MyGlobals::transFolderName + "\r\n";

	textBox1->Text = in + in4;
	richTextBox2->Text = "Transcripting ...";

	using namespace System;
	using namespace System::IO;
	try {
		if (Directory::Exists(MyGlobals::transFolderName)) {
			Console::WriteLine("TRANS Directory already exists.");
		}
		else {
			DirectoryInfo ^ di = Directory::CreateDirectory(MyGlobals::transFolderName);
		}

	}
	catch (Exception ^ e) {
		Console::WriteLine("Failed to create TRANS directory " + MyGlobals::transFolderName, e);
	}




	thread4->Name = "transImport";
	thread4_run = true;
	thread4->Start();

	thread5 = gcnew Thread(gcnew ThreadStart(this, &MyForm::ThreadFunction2));
	thread5_run = true;
	thread5->Start();


}
private: void transImport() {


	String ^ commandString = "";
	std::string commandStr = "";
	const char* commandChar;

	using namespace Runtime::InteropServices;

	Console::WriteLine("python -W ignore transcribe_async_short_file3_44.py " + MyGlobals::importFileName + " " + MyGlobals::folderParameter);

	commandString = "python -W ignore transcribe_async_short_file3_44.py " + MyGlobals::importFileName + " " + MyGlobals::folderParameter;
	commandChar = (const char*)(Marshal::StringToHGlobalAnsi(commandString)).ToPointer();
	commandStr = commandChar;
	Marshal::FreeHGlobal(IntPtr((void*)commandChar));

	system(commandStr.c_str());

}
private: System::Void textBox3_Click(System::Object^  sender, System::EventArgs^  e) {
	Console::WriteLine("Searching text clicked");

	textBox3->Text = "";
	textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
}


private: void ThreadFunction();
private: void ThreadFunction2();

public: int main() {
	printf("Thread - MAIN THREAD.... \r\n");
	//MyForm^ meForm = gcnew MyForm;
	//meForm->showDialog();
	//meForm->InitializeComponent();

	main_thread_run = true;
	/*while (main_thread_run) {
		printf("Thread - MAIN THREAD. 2... \r\n");

		Thread::Sleep(1000);

	}*

	/*
Console::WriteLine("Expect to read file, " + MyGlobals::transFolderName + "Sample_transcript.txt");

		//DateTime transDt = File::GetLastWriteTime(MyGlobals::transFolderName);
		//Console::WriteLine("lastWriteTime - TRANS :" + transDt);


		String ^transTest = "C:\\EEP-P13\\IM-Proj\\TEST\\Sample_transcript.txt";
		FileStream^ fs = gcnew FileStream(transTest, FileMode::Open, FileAccess::Read, FileShare::ReadWrite);
		StreamReader^ sr = gcnew StreamReader(fs);
		String ^ tranStr;

		DateTime testDt = File::GetLastWriteTime(transTest);
		Console::WriteLine("lastWriteTime - TEST, " + transTest + "," + testDt);

		if (MyGlobals::trans_update_dt != testDt) {
			Console::WriteLine("old trans_update_dt ---" + MyGlobals::trans_update_dt);
			Console::WriteLine("new trans_update_dt ---" + testDt);

			MyGlobals::trans_update_dt = testDt;
			trans_update = true;
		}

		if (trans_update) {
			Console::WriteLine("here I am ");

			while ((tranStr = sr->ReadLine()) != nullptr)
			{
				//MyGlobals::
				//meForm->richTextBox2->AppendText(tranStr + "\n");
				//char* tranChar = new char*(tranStr);
				//MyGlobals::richTextBox2->Text = "hello";
				Console::WriteLine(tranStr);
				//backgroundWorker1->RunWorkerAsync();
				//if (richTextBox2->InvokeRequired) {
				//	StringArgReturningVoidDelegate^ d = gcnew StringArgReturningVoidDelegate(this, &Project3::MyForm::checkUpdFile);
				//	Invoke(d);
				//std::string name = "";
				//richTextBox2->Invoke(gcnew MethodInvoker(delegate{ name = richTextBox2->Text; }));
				//}
				//else
				//{
				//richTextBox2->Text = tranStr;
				//}
			};
			sr->Close();
			trans_update = false;
		}
		*/
/*
}
*/
	
	return 0;
}




};

// The following code assumes a 'ListBox' and a 'Button' control are added to a form,
// containing a delegate which encapsulates a method that adds items to the listbox.
public ref class MyThreadClass
{
private:
	MyForm ^ myForm1;

public:
	MyThreadClass(MyForm^ myForm)
	{
		myForm1 = myForm;
	}

	void Run()
	{
		// Execute the specified delegate on the thread that owns
		// 'myFormControl1' control's underlying window handle.
		while (thread3_run) {
			printf("Thread - readDisplay\r\n");
			myForm1->Invoke(myForm1->myDelegate);
			Thread::Sleep(10000);
		}
	}
	void Run2()
	{
		while (thread5_run) {
			myForm1->Invoke(myForm1->myDelegate2);
			Thread::Sleep(10000);
		}

	}
};

void MyForm::ThreadFunction() {
	MyThreadClass^ myThreadClassObject = gcnew MyThreadClass(this);
	myThreadClassObject->Run();
}
void MyForm::ThreadFunction2() {
	MyThreadClass^ myThreadClassObject = gcnew MyThreadClass(this);
	myThreadClassObject->Run2();
}


}


