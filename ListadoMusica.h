#pragma once

#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <string>

namespace ListadoMusica {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for ListadoMusica
	/// </summary>
	public ref class ListadoMusica : public System::Windows::Forms::Form
	{
	public:
		ListadoMusica(void)
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
		~ListadoMusica()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnAbrir;
	protected:

	private: System::Windows::Forms::TextBox^ txtDirectorio;
	protected:

	protected:

	protected:

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ListBox^ lbAlbums;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ btnBuscar;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		void mostrarDialogoSeleccionarDirectorio(Form^ formulario, TextBox^ cajaTexto) {
			// instancia de FolderBrowserDialog 
			FolderBrowserDialog^ dialogo = gcnew FolderBrowserDialog();

			// Establecer la propiedad Description para mostrar un mensaje en el cuadro de diálogo
			dialogo->Description = "Selecciona un directorio";

			// Establecer la propiedad RootFolder para indicar la carpeta de nivel superior que aparecerá en la vista de árbol
			dialogo->RootFolder = Environment::SpecialFolder::MyComputer;

			// Mostrar el cuadro de diálogo y obtener el resultado
			System::Windows::Forms::DialogResult resultado = dialogo->ShowDialog(formulario);

			// Verificar si el usuario presionó el botón Aceptar
			if (resultado == System::Windows::Forms::DialogResult::OK)
			{
				// Obtener la ruta del directorio seleccionado
				String^ ruta = dialogo->SelectedPath;

				// Mostrar la ruta en el TextBox
				cajaTexto->Text = ruta;
			}

		}

		array<String^>^ obtenerListadoDirectorio(String^ directorio, String^ filtro) {
			// Crear un array de strings para almacenar los nombres de los archivos 
			array<String^>^ archivos;

			// Usar un bloque try-catch para manejar posibles excepciones
			try
			{
				// Usar la clase Directory para obtener los archivos que coincidan con el filtro
				archivos = Directory::GetFiles(directorio, filtro);

				// Devolver el array de archivos
				return archivos;
			}
			catch (Exception^ e)
			{
				// Mostrar el mensaje de error en caso de excepción
				Console::WriteLine(e->Message);

				// Devolver null en caso de error
				return nullptr;
			}

		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnAbrir = (gcnew System::Windows::Forms::Button());
			this->txtDirectorio = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lbAlbums = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnBuscar = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnAbrir
			// 
			this->btnAbrir->Location = System::Drawing::Point(123, 8);
			this->btnAbrir->Name = L"btnAbrir";
			this->btnAbrir->Size = System::Drawing::Size(177, 23);
			this->btnAbrir->TabIndex = 0;
			this->btnAbrir->Text = L"Abrir Directorio";
			this->btnAbrir->UseVisualStyleBackColor = true;
			this->btnAbrir->Click += gcnew System::EventHandler(this, &ListadoMusica::btnBuscar_Click);
			// 
			// txtDirectorio
			// 
			this->txtDirectorio->Enabled = false;
			this->txtDirectorio->Location = System::Drawing::Point(13, 31);
			this->txtDirectorio->Name = L"txtDirectorio";
			this->txtDirectorio->Size = System::Drawing::Size(287, 20);
			this->txtDirectorio->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(104, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Directorio de Musica";
			// 
			// lbAlbums
			// 
			this->lbAlbums->FormattingEnabled = true;
			this->lbAlbums->Location = System::Drawing::Point(12, 103);
			this->lbAlbums->Name = L"lbAlbums";
			this->lbAlbums->Size = System::Drawing::Size(288, 264);
			this->lbAlbums->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Albums";
			// 
			// btnBuscar
			// 
			this->btnBuscar->Location = System::Drawing::Point(60, 79);
			this->btnBuscar->Name = L"btnBuscar";
			this->btnBuscar->Size = System::Drawing::Size(240, 23);
			this->btnBuscar->TabIndex = 5;
			this->btnBuscar->Text = L"Buscar Albums";
			this->btnBuscar->UseVisualStyleBackColor = true;
			this->btnBuscar->Click += gcnew System::EventHandler(this, &ListadoMusica::btnBuscar_Click_1);
			// 
			// ListadoMusica
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(757, 374);
			this->Controls->Add(this->btnBuscar);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->lbAlbums);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtDirectorio);
			this->Controls->Add(this->btnAbrir);
			this->Name = L"ListadoMusica";
			this->Text = L"ListadoMusica";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void btnBuscar_Click(System::Object^ sender, System::EventArgs^ e) {
			this->mostrarDialogoSeleccionarDirectorio(this, this->txtDirectorio);
		}
		private: System::Void btnBuscar_Click_1(System::Object^ sender, System::EventArgs^ e) {
			array<String^>^ archivos = this->obtenerListadoDirectorio(this->txtDirectorio->Text, "*.txt");
			this->lbAlbums->Items->Clear();
			for (int i = 0; i < archivos->Length; i++) {
				this->lbAlbums->Items->Add(archivos[i]->Replace(this->txtDirectorio->Text + "\\", "")->Replace(".txt", ""));
			}
		}
};
}
