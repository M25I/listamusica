#pragma once

#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <string>
#include "Album.h"
#include "Cancion.h"

namespace ListadoMusica {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
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
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ListBox^ lbCanciones;

	private: System::Windows::Forms::Button^ btnNext;

	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ lblDuracion;
	private: System::Windows::Forms::Label^ lbl;
	private: System::Windows::Forms::Label^ lblCancion;
	private: System::Windows::Forms::Label^ lblArtista;
	private: System::Windows::Forms::Label^ lblAlbum;
	private: System::Windows::Forms::Button^ btnAgregar;
	private: System::Windows::Forms::Button^ btnOrdenar;


	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::RadioButton^ rBDesc;
	private: System::Windows::Forms::RadioButton^ rBAsc;



	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::RadioButton^ rBCancion;

	private: System::Windows::Forms::RadioButton^ rBArtista;

	private: System::Windows::Forms::RadioButton^ rBAlbum;
	private: System::Windows::Forms::RadioButton^ rBDuracion;
	private: System::Windows::Forms::Splitter^ splitter1;
	private: System::Windows::Forms::DataGridView^ gvCola;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ clAlbum;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ clCancion;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ clArtista;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ clDuracion;
	private: System::Windows::Forms::Button^ btnPlay;













		List<Album^>^ albums = gcnew List<Album^>();
		List<Cancion^>^ playlist = gcnew List<Cancion^>(); //Cola

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

		List<Cancion^>^ CargarCanciones(String^ nombreArchivo, String^ nombreAlbum) {
			List<Cancion^>^ canciones = gcnew List<Cancion^>();
			// Crear un objeto StreamReader para abrir el archivo
			try
			{
				Console::WriteLine("Abriendo archivo ", nombreArchivo);
				StreamReader^ din = File::OpenText(nombreArchivo);

				String^ str;
				int count = 0;
				while ((str = din->ReadLine()) != nullptr)
				{
					count++;
					Console::WriteLine("line {0}: {1}", count, str);
					array<String^>^ datos = str->Split('|');
					Cancion^ cancion = gcnew Cancion();
					cancion->nombre = datos[0];
					cancion->cantante = datos[2];
					cancion->duracion = datos[4];
					cancion->nombreAlbum = nombreAlbum;
					canciones->Add(cancion);
				}
			}
			catch (Exception^ e)
			{
				if (dynamic_cast<FileNotFoundException^>(e))
					Console::WriteLine("Archivo '{0}' no encontrado", nombreArchivo);
				else
					Console::WriteLine("Problema al leer archivo '{0}'", nombreArchivo);
			}

			return canciones;
		}

		void refrescarCola() {
			gvCola->Rows->Clear();
			for each  (Cancion^ cancion in playlist)
			{
				gvCola->Rows->Add();
				int numFilas = gvCola->Rows->Count - 1;
				gvCola->Rows[numFilas]->Cells[0]->Value = cancion->nombreAlbum;
				gvCola->Rows[numFilas]->Cells[1]->Value = cancion->nombre;
				gvCola->Rows[numFilas]->Cells[2]->Value = cancion->cantante;
				gvCola->Rows[numFilas]->Cells[3]->Value = cancion->duracion;
			}
		}

		static int compareByAlbum(Cancion^ a, Cancion^ b) {
			return  (a->nombreAlbum->CompareTo(b->nombreAlbum));
		}

		static int compareByCancion(Cancion^ a, Cancion^ b) {
			return  (a->nombre->CompareTo(b->nombre));
		}

		static int compareByArtista(Cancion^ a, Cancion^ b) {
			return  (a->cantante->CompareTo(b->cantante));
		}

		static int compareByDuracion(Cancion^ a, Cancion^ b) {
			return  (a->duracion->CompareTo(b->duracion));
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ListadoMusica::typeid));
			this->btnAbrir = (gcnew System::Windows::Forms::Button());
			this->txtDirectorio = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lbAlbums = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btnBuscar = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lbCanciones = (gcnew System::Windows::Forms::ListBox());
			this->btnNext = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->lblDuracion = (gcnew System::Windows::Forms::Label());
			this->lbl = (gcnew System::Windows::Forms::Label());
			this->lblCancion = (gcnew System::Windows::Forms::Label());
			this->lblArtista = (gcnew System::Windows::Forms::Label());
			this->lblAlbum = (gcnew System::Windows::Forms::Label());
			this->btnAgregar = (gcnew System::Windows::Forms::Button());
			this->btnOrdenar = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->rBDesc = (gcnew System::Windows::Forms::RadioButton());
			this->rBAsc = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->rBDuracion = (gcnew System::Windows::Forms::RadioButton());
			this->rBCancion = (gcnew System::Windows::Forms::RadioButton());
			this->rBArtista = (gcnew System::Windows::Forms::RadioButton());
			this->rBAlbum = (gcnew System::Windows::Forms::RadioButton());
			this->splitter1 = (gcnew System::Windows::Forms::Splitter());
			this->gvCola = (gcnew System::Windows::Forms::DataGridView());
			this->clAlbum = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->clCancion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->clArtista = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->clDuracion = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->btnPlay = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gvCola))->BeginInit();
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
			this->lbAlbums->SelectedIndexChanged += gcnew System::EventHandler(this, &ListadoMusica::lbAlbums_SelectedIndexChanged);
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
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(307, 84);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(57, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Canciones";
			// 
			// lbCanciones
			// 
			this->lbCanciones->FormattingEnabled = true;
			this->lbCanciones->Location = System::Drawing::Point(306, 103);
			this->lbCanciones->Name = L"lbCanciones";
			this->lbCanciones->Size = System::Drawing::Size(288, 264);
			this->lbCanciones->TabIndex = 6;
			// 
			// btnNext
			// 
			this->btnNext->Location = System::Drawing::Point(1002, 127);
			this->btnNext->Name = L"btnNext";
			this->btnNext->Size = System::Drawing::Size(75, 37);
			this->btnNext->TabIndex = 9;
			this->btnNext->Text = L"Siguiente";
			this->btnNext->UseVisualStyleBackColor = true;
			this->btnNext->Click += gcnew System::EventHandler(this, &ListadoMusica::btnNext_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(768, 31);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(127, 128);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 11;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(929, 67);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(148, 54);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 12;
			this->pictureBox2->TabStop = false;
			// 
			// lblDuracion
			// 
			this->lblDuracion->AutoSize = true;
			this->lblDuracion->Location = System::Drawing::Point(1083, 89);
			this->lblDuracion->Name = L"lblDuracion";
			this->lblDuracion->Size = System::Drawing::Size(50, 13);
			this->lblDuracion->TabIndex = 13;
			this->lblDuracion->Text = L"Duracion";
			// 
			// lbl
			// 
			this->lbl->AutoSize = true;
			this->lbl->Location = System::Drawing::Point(901, 89);
			this->lbl->Name = L"lbl";
			this->lbl->Size = System::Drawing::Size(22, 13);
			this->lbl->TabIndex = 14;
			this->lbl->Text = L"0:0";
			// 
			// lblCancion
			// 
			this->lblCancion->AutoSize = true;
			this->lblCancion->Font = (gcnew System::Drawing::Font(L"MV Boli", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblCancion->Location = System::Drawing::Point(926, 31);
			this->lblCancion->Name = L"lblCancion";
			this->lblCancion->Size = System::Drawing::Size(59, 17);
			this->lblCancion->TabIndex = 15;
			this->lblCancion->Text = L"Canción";
			// 
			// lblArtista
			// 
			this->lblArtista->AutoSize = true;
			this->lblArtista->Location = System::Drawing::Point(926, 51);
			this->lblArtista->Name = L"lblArtista";
			this->lblArtista->Size = System::Drawing::Size(36, 13);
			this->lblArtista->TabIndex = 16;
			this->lblArtista->Text = L"Artista";
			// 
			// lblAlbum
			// 
			this->lblAlbum->BackColor = System::Drawing::Color::Transparent;
			this->lblAlbum->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->lblAlbum->Font = (gcnew System::Drawing::Font(L"MV Boli", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lblAlbum->ForeColor = System::Drawing::Color::Black;
			this->lblAlbum->Location = System::Drawing::Point(768, 130);
			this->lblAlbum->Name = L"lblAlbum";
			this->lblAlbum->Size = System::Drawing::Size(127, 34);
			this->lblAlbum->TabIndex = 17;
			this->lblAlbum->Text = L"Album";
			this->lblAlbum->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnAgregar
			// 
			this->btnAgregar->Location = System::Drawing::Point(393, 79);
			this->btnAgregar->Name = L"btnAgregar";
			this->btnAgregar->Size = System::Drawing::Size(201, 23);
			this->btnAgregar->TabIndex = 18;
			this->btnAgregar->Text = L"Agregar canción a cola";
			this->btnAgregar->UseVisualStyleBackColor = true;
			this->btnAgregar->Click += gcnew System::EventHandler(this, &ListadoMusica::btnAgregar_Click);
			// 
			// btnOrdenar
			// 
			this->btnOrdenar->Location = System::Drawing::Point(615, 344);
			this->btnOrdenar->Name = L"btnOrdenar";
			this->btnOrdenar->Size = System::Drawing::Size(75, 23);
			this->btnOrdenar->TabIndex = 19;
			this->btnOrdenar->Text = L"Ordenar";
			this->btnOrdenar->UseVisualStyleBackColor = true;
			this->btnOrdenar->Click += gcnew System::EventHandler(this, &ListadoMusica::btnOrdenar_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->rBDesc);
			this->groupBox1->Controls->Add(this->rBAsc);
			this->groupBox1->Location = System::Drawing::Point(600, 84);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(111, 100);
			this->groupBox1->TabIndex = 20;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Orden";
			// 
			// rBDesc
			// 
			this->rBDesc->AutoSize = true;
			this->rBDesc->Location = System::Drawing::Point(8, 51);
			this->rBDesc->Name = L"rBDesc";
			this->rBDesc->Size = System::Drawing::Size(89, 17);
			this->rBDesc->TabIndex = 1;
			this->rBDesc->Text = L"Descendente";
			this->rBDesc->UseVisualStyleBackColor = true;
			// 
			// rBAsc
			// 
			this->rBAsc->AutoSize = true;
			this->rBAsc->Checked = true;
			this->rBAsc->Location = System::Drawing::Point(8, 28);
			this->rBAsc->Name = L"rBAsc";
			this->rBAsc->Size = System::Drawing::Size(82, 17);
			this->rBAsc->TabIndex = 0;
			this->rBAsc->TabStop = true;
			this->rBAsc->Text = L"Ascendente";
			this->rBAsc->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->rBDuracion);
			this->groupBox2->Controls->Add(this->rBCancion);
			this->groupBox2->Controls->Add(this->rBArtista);
			this->groupBox2->Controls->Add(this->rBAlbum);
			this->groupBox2->Location = System::Drawing::Point(600, 207);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(111, 114);
			this->groupBox2->TabIndex = 21;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Ordenar por";
			// 
			// rBDuracion
			// 
			this->rBDuracion->AutoSize = true;
			this->rBDuracion->Location = System::Drawing::Point(8, 89);
			this->rBDuracion->Name = L"rBDuracion";
			this->rBDuracion->Size = System::Drawing::Size(68, 17);
			this->rBDuracion->TabIndex = 5;
			this->rBDuracion->Text = L"Duración";
			this->rBDuracion->UseVisualStyleBackColor = true;
			// 
			// rBCancion
			// 
			this->rBCancion->AutoSize = true;
			this->rBCancion->Location = System::Drawing::Point(8, 66);
			this->rBCancion->Name = L"rBCancion";
			this->rBCancion->Size = System::Drawing::Size(64, 17);
			this->rBCancion->TabIndex = 4;
			this->rBCancion->Text = L"Canción";
			this->rBCancion->UseVisualStyleBackColor = true;
			// 
			// rBArtista
			// 
			this->rBArtista->AutoSize = true;
			this->rBArtista->Location = System::Drawing::Point(8, 43);
			this->rBArtista->Name = L"rBArtista";
			this->rBArtista->Size = System::Drawing::Size(54, 17);
			this->rBArtista->TabIndex = 3;
			this->rBArtista->Text = L"Artista";
			this->rBArtista->UseVisualStyleBackColor = true;
			// 
			// rBAlbum
			// 
			this->rBAlbum->AutoSize = true;
			this->rBAlbum->Checked = true;
			this->rBAlbum->Location = System::Drawing::Point(8, 20);
			this->rBAlbum->Name = L"rBAlbum";
			this->rBAlbum->Size = System::Drawing::Size(54, 17);
			this->rBAlbum->TabIndex = 2;
			this->rBAlbum->TabStop = true;
			this->rBAlbum->Text = L"Album";
			this->rBAlbum->UseVisualStyleBackColor = true;
			// 
			// splitter1
			// 
			this->splitter1->Location = System::Drawing::Point(0, 0);
			this->splitter1->Name = L"splitter1";
			this->splitter1->Size = System::Drawing::Size(3, 374);
			this->splitter1->TabIndex = 22;
			this->splitter1->TabStop = false;
			// 
			// gvCola
			// 
			this->gvCola->AllowUserToAddRows = false;
			this->gvCola->AllowUserToDeleteRows = false;
			this->gvCola->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gvCola->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->clAlbum, this->clCancion,
					this->clArtista, this->clDuracion
			});
			this->gvCola->Location = System::Drawing::Point(717, 188);
			this->gvCola->Name = L"gvCola";
			this->gvCola->ReadOnly = true;
			this->gvCola->Size = System::Drawing::Size(416, 169);
			this->gvCola->TabIndex = 23;
			// 
			// clAlbum
			// 
			this->clAlbum->HeaderText = L"Album";
			this->clAlbum->Name = L"clAlbum";
			this->clAlbum->ReadOnly = true;
			// 
			// clCancion
			// 
			this->clCancion->HeaderText = L"Canción";
			this->clCancion->Name = L"clCancion";
			this->clCancion->ReadOnly = true;
			// 
			// clArtista
			// 
			this->clArtista->HeaderText = L"Artista";
			this->clArtista->Name = L"clArtista";
			this->clArtista->ReadOnly = true;
			// 
			// clDuracion
			// 
			this->clDuracion->HeaderText = L"Duración";
			this->clDuracion->Name = L"clDuracion";
			this->clDuracion->ReadOnly = true;
			// 
			// btnPlay
			// 
			this->btnPlay->Location = System::Drawing::Point(929, 127);
			this->btnPlay->Name = L"btnPlay";
			this->btnPlay->Size = System::Drawing::Size(67, 37);
			this->btnPlay->TabIndex = 24;
			this->btnPlay->Text = L"Play";
			this->btnPlay->UseVisualStyleBackColor = true;
			this->btnPlay->Click += gcnew System::EventHandler(this, &ListadoMusica::btnPlay_Click);
			// 
			// ListadoMusica
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::LightGreen;
			this->ClientSize = System::Drawing::Size(1138, 374);
			this->Controls->Add(this->btnPlay);
			this->Controls->Add(this->gvCola);
			this->Controls->Add(this->splitter1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnOrdenar);
			this->Controls->Add(this->btnAgregar);
			this->Controls->Add(this->lblAlbum);
			this->Controls->Add(this->lblArtista);
			this->Controls->Add(this->lblCancion);
			this->Controls->Add(this->lbl);
			this->Controls->Add(this->lblDuracion);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->btnNext);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->lbCanciones);
			this->Controls->Add(this->btnBuscar);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->lbAlbums);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtDirectorio);
			this->Controls->Add(this->btnAbrir);
			this->Name = L"ListadoMusica";
			this->Text = L"ListadoMusica";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->gvCola))->EndInit();
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
			this->lbCanciones->Items->Clear();
			this->gvCola->Rows->Clear();
			this->playlist->Clear();
			albums->Clear();
			for (int i = 0; i < archivos->Length; i++) {
				String^ nombre = archivos[i]->Replace(this->txtDirectorio->Text + "\\", "")->Replace(".txt", "");
				this->lbAlbums->Items->Add(nombre);
				Album^ album = gcnew Album();
				album->nombre = nombre;
				album->canciones = CargarCanciones(archivos[i], nombre);
				albums->Add(album);

			}
		}
		private: System::Void lbAlbums_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
			// Obtiene el album seleccionado en listbox
			String^ nombreAlbum = lbAlbums->SelectedItem->ToString();
			for each (Album^ album in albums) {
				if (album->nombre->Equals(nombreAlbum)) {
					lbCanciones->Items->Clear();
					for each (Cancion ^ cancion in album->canciones) {
						lbCanciones->Items->Add(cancion->nombre + " - " + cancion->cantante + " - " + cancion->duracion);
					}
				}
			}
		}
	private: System::Void btnAgregar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ nombreAlbum = lbAlbums->SelectedItem->ToString();
		String^ nombreCancion = lbCanciones->SelectedItem->ToString();
		array<String^>^ datos = nombreCancion->Split('-');

		Cancion^ cancion = gcnew Cancion(); 
		cancion->nombreAlbum = nombreAlbum;

		cancion->nombre = datos[0]->Trim();
		cancion->cantante = datos[1]->Trim();
		cancion->duracion = datos[2]->Trim();

		playlist->Add(cancion);

		refrescarCola();
	}
private: System::Void btnPlay_Click(System::Object^ sender, System::EventArgs^ e) {
	lblAlbum->Text = gvCola->Rows[0]->Cells[0]->Value->ToString();
	lblCancion->Text = gvCola->Rows[0]->Cells[1]->Value->ToString();
	lblArtista->Text = gvCola->Rows[0]->Cells[2]->Value->ToString();
	lblDuracion->Text= gvCola->Rows[0]->Cells[3]->Value->ToString(); 
}
private: System::Void btnNext_Click(System::Object^ sender, System::EventArgs^ e) {
	Cancion^ cancion = playlist[0];
	playlist->RemoveAt(0);
	playlist->Add(cancion);

	refrescarCola();
}
private: System::Void btnOrdenar_Click(System::Object^ sender, System::EventArgs^ e) {
	if (rBAlbum->Checked == true) {
		Comparison<Cancion^>^ comparisonDelegate = gcnew Comparison<Cancion^>(&compareByAlbum);
		playlist->Sort(comparisonDelegate);
	}

	if (rBCancion->Checked == true) {
		Comparison<Cancion^>^ comparisonDelegate = gcnew Comparison<Cancion^>(&compareByCancion);
		playlist->Sort(comparisonDelegate);
	}

	if (rBArtista->Checked == true) {
		Comparison<Cancion^>^ comparisonDelegate = gcnew Comparison<Cancion^>(&compareByArtista);
		playlist->Sort(comparisonDelegate);
	}

	if (rBDuracion->Checked == true) {
		Comparison<Cancion^>^ comparisonDelegate = gcnew Comparison<Cancion^>(&compareByDuracion);
		playlist->Sort(comparisonDelegate);
	}

	if (rBDesc->Checked == true) {
		playlist->Reverse();
	}

	refrescarCola();
}
};
}
