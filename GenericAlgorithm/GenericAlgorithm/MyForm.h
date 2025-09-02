#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <random>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>


#define _CRT_SECURE_NO_WARNINGS

const int POPULATION_SIZE = 50;
const int NUM_GENERATIONS = 250;
const int TOURNAMENT_SIZE = 5;
const double MUTATION_RATE = 0.5;


std::mt19937 rng(static_cast<unsigned>(std::time(0)));

using namespace std;
using namespace std::chrono;


namespace GenericAlgorithm {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Data::SqlClient;
	using namespace System::Drawing;
	using namespace System::IO;
	
	//ГЕНЕТИЧЕСКИЙ алгоритм
	
	struct NodeState {

			int id;
			int blade1_corr;
			int blade2_corr;
			int blade3_corr;
			int blade1_md;
			int blade2_md;
			int blade3_md;
			int blade1_ice;
			int blade2_ice;
			int blade3_ice;
			int blade1_err;
			int blade2_err;
			int blade3_err;
			int rotor_corr;
			int rotor_md;
			int rotor_ice;
			int gondola_corr;
			int gondola_md;
			int mast_corr;
			int mast_md;
			int generator_cond;
			int sensors_cond;
			int electronics_cond;
		
		// Конструктор для инициализации всех значений
		NodeState(int id = 0, int blade1_corr = 0, int blade2_corr = 0, int blade3_corr = 0,
			int blade1_md = 0, int blade2_md = 0, int blade3_md = 0,
			int blade1_ice = 0, int blade2_ice = 0, int blade3_ice = 0,
			int blade1_err = 0, int blade2_err = 0, int blade3_err = 0,
			int rotor_corr = 0, int rotor_md = 0, int rotor_ice = 0,
			int gondola_corr = 0, int gondola_md = 0,
			int mast_corr = 0, int mast_md = 0,
			int generator_cond = 0, int sensors_cond = 0, int electronics_cond = 0)
			: id(id), blade1_corr(blade1_corr), blade2_corr(blade2_corr), blade3_corr(blade3_corr),
			blade1_md(blade1_md), blade2_md(blade2_md), blade3_md(blade3_md),
			blade1_ice(blade1_ice), blade2_ice(blade2_ice), blade3_ice(blade3_ice),
			blade1_err(blade1_err), blade2_err(blade2_err), blade3_err(blade3_err),
			rotor_corr(rotor_corr), rotor_md(rotor_md), rotor_ice(rotor_ice),
			gondola_corr(gondola_corr), gondola_md(gondola_md),
			mast_corr(mast_corr), mast_md(mast_md),
			generator_cond(generator_cond), sensors_cond(sensors_cond),
			electronics_cond(electronics_cond)
		{
		}
	};
	std::vector<std::vector<int>> create_wind_turbine_graph() {
		std::vector<std::vector<int>> G(6);
		G[1] = { 2, 3 };
		G[2] = { 1, 4 };
		G[3] = { 1, 5 };
		G[4] = { 2 };
		G[5] = { 3 };
		return G;
	}	
	

	



	
	vector<vector<NodeState>> initialize_population(int size, int num_nodes, vector<vector<int>> data) {
		vector<vector<NodeState>> population(size, vector<NodeState>(num_nodes));

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < num_nodes; ++j) {
				// Предполагаем, что каждая строка в data содержит все необходимые значения для создания NodeState
				if (i < data.size() && j < data[i].size()) {
					// Убедитесь, что в data есть достаточно значений для инициализации NodeState
					if (data[i].size() >= 21) { // Учитывая количество полей в NodeState
						population[i][j] = NodeState(
							data[i][0],   // id
							data[i][1],   // blade1_corr
							data[i][2],   // blade2_corr
							data[i][3],   // blade3_corr
							data[i][4],   // blade1_md
							data[i][5],   // blade2_md
							data[i][6],   // blade3_md
							data[i][7],   // blade1_ice
							data[i][8],   // blade2_ice
							data[i][9],   // blade3_ice
							data[i][10],  // blade1_err
							data[i][11],  // blade2_err
							data[i][12],  // blade3_err
							data[i][13],  // rotor_corr
							data[i][14],  // rotor_md
							data[i][15],  // rotor_ice
							data[i][16],  // gondola_corr
							data[i][17],  // gondola_md
							data[i][18],  // mast_corr
							data[i][19],  // mast_md
							data[i][20],  // generator_cond
							data[i][21],  // sensors_cond
							data[i][22]  // electronics_cond
						);
					}
				}
			}
		}
		return population;
	}
	std::vector<NodeState> crossover(const std::vector<NodeState>& parent1,
		const std::vector<NodeState>& parent2) {

		//Создаем новый индивид (потомка)
		std::vector<NodeState> child(parent1.size());

		//Случайным образом присваиваем характеристикам потомка
		//значения параметров родительских индивидов
		for (size_t i = 1; i < parent1.size(); ++i) {
			child[i] = (rng() % 2) ? parent1[i] : parent2[i];
		}
		return child;
	}



	void mutate(std::vector<NodeState>& individual, double mutation_rate) {
		for (size_t i = 0; i < individual.size(); ++i) {
			// Генерируем случайное число от 0 до 1

			double p = rng() % 1;
			if (p < mutation_rate) {
				// Применяем мутацию к полям NodeState
				individual[i].blade1_corr = 5 - individual[i].blade1_corr;
				individual[i].blade2_corr = 5 - individual[i].blade2_corr;
				individual[i].blade3_corr = 5 - individual[i].blade3_corr;
				individual[i].blade1_md = 5 - individual[i].blade1_md;
				individual[i].blade2_md = 5 - individual[i].blade2_md;
				individual[i].blade3_md = 5 - individual[i].blade3_md;
				individual[i].blade1_ice = 5 - individual[i].blade1_ice;
				individual[i].blade2_ice = 5 - individual[i].blade2_ice;
				individual[i].blade3_ice = 5 - individual[i].blade3_ice;
				individual[i].blade1_err = 5 - individual[i].blade1_err;
				individual[i].blade2_err = 5 - individual[i].blade2_err;
				individual[i].blade3_err = 5 - individual[i].blade3_err;
				individual[i].rotor_corr = 5 - individual[i].rotor_corr;
				individual[i].rotor_md = 5 - individual[i].rotor_md;
				individual[i].rotor_ice = 5 - individual[i].rotor_ice;
				individual[i].gondola_corr = 5 - individual[i].gondola_corr;
				individual[i].gondola_md = 5 - individual[i].gondola_md;
				individual[i].mast_corr = 5 - individual[i].mast_corr;
				individual[i].mast_md = 5 - individual[i].mast_md;
				individual[i].generator_cond = 5 - individual[i].generator_cond;
				individual[i].sensors_cond = 5 - individual[i].sensors_cond;
				individual[i].electronics_cond = 5 - individual[i].electronics_cond;
			}
		}
	}
	double fitness(const std::vector<NodeState>& individual, const std::vector<std::vector<int>>& G) {
		double fitness_value = 0.0;
		for (int node = 1; node < G.size(); ++node) {
			const auto& state = individual[node];
			fitness_value += state.blade1_corr * 0.042;
			fitness_value += state.blade2_corr * 0.042;
			fitness_value += state.blade3_corr * 0.042;
			fitness_value += state.blade1_md * 0.042;
			fitness_value += state.blade2_md * 0.042;
			fitness_value += state.blade3_md * 0.042;
			fitness_value += state.blade1_ice * 0.042;
			fitness_value += state.blade2_ice * 0.042;
			fitness_value += state.blade3_ice * 0.042;
			fitness_value += state.blade1_err * 0.042;
			fitness_value += state.blade2_err * 0.042;
			fitness_value += state.blade3_err * 0.042;

			fitness_value += state.rotor_corr * 0.036;
			fitness_value += state.rotor_md * 0.036;
			fitness_value += state.rotor_ice * 0.036;

			fitness_value += state.gondola_corr * 0.036;
			fitness_value += state.gondola_md * 0.036;

			fitness_value += state.mast_corr * 0.036;
			fitness_value += state.mast_md * 0.036;

			fitness_value += state.generator_cond * 0.083;
			fitness_value += state.sensors_cond * 0.083;
			fitness_value += state.electronics_cond * 0.083;
		}
		return fitness_value;
	}
	// Турнирный отбор
	vector<NodeState> tournament_selection(const vector<vector<NodeState>>& population,
		const vector<double>& fitnesses, int k) {

		vector<int> selected;

		for (int i = 0; i < k; ++i) {
			int ind = rng() % population.size();
			selected.push_back(ind);
		}

		int best = selected[0];

		for (int i = 1; i < k; ++i) {
			if (fitnesses[selected[i]] > fitnesses[best]) {
				best = selected[i];
			}
		}
		return population[best];
	}

	pair<vector<NodeState>, double> genetic_algorithm(const vector<vector<int>>& G, int population_size,
		int num_generations, int tournament_size, double mutation_rate, vector<vector<int>> data) {
		int num_nodes = G.size();
		auto population = initialize_population(population_size, num_nodes, data);
		vector<NodeState> best_individual;
		double best_fitness = -numeric_limits<double>::infinity();

		for (int generation = 0; generation < num_generations; ++generation) {
			vector<double> fitnesses(population_size);
			for (int i = 0; i < population_size; ++i) {
				fitnesses[i] = fitness(population[i], G);
			}

			vector<vector<NodeState>> new_population;
			for (int i = 0; i < population_size; ++i) {
				auto parent1 = tournament_selection(population, fitnesses, tournament_size);
				auto parent2 = tournament_selection(population, fitnesses, tournament_size);
				auto child = crossover(parent1, parent2);
				mutate(child, mutation_rate);
				new_population.push_back(child);
			}

			population = new_population;
			auto best_in_pop = std::max_element(fitnesses.begin(), fitnesses.end());
			double best_fitness_in_population = *best_in_pop;
			int best_index = std::distance(fitnesses.begin(), best_in_pop);

			if (best_fitness_in_population > best_fitness) {
				best_fitness = best_fitness_in_population;
				best_individual = population[best_index];
			}

			std::cout << "Generation " << generation << ": Best Fitness = " << best_fitness << std::endl;
		}

		return { best_individual, best_fitness };
	}


	


	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			pwd->PasswordChar = '*';
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ param_btn;

	protected:
	private: System::Windows::Forms::DataGridView^ db_table;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ опцииToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ показатьТаблицуToolStripMenuItem;
	private: System::Windows::Forms::TextBox^ result_field;
	private: System::Windows::Forms::Button^ start_btn;
	private: System::Windows::Forms::TextBox^ login;
	private: System::Windows::Forms::TextBox^ pwd;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::Button^ auth_btn;
	private: System::Windows::Forms::DataGridView^ db_select;
	private: System::Windows::Forms::Button^ load_list_btn;
	private: System::Windows::Forms::ToolStripMenuItem^ справкаToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::Button^ save_btn;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::ComponentModel::IContainer^ components;

	private: System::Windows::Forms::TextBox^ save_csv_field;
	private: System::Windows::Forms::TextBox^ save_db_csv_field;

	private: String^ selected_db;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->param_btn = (gcnew System::Windows::Forms::Button());
			this->db_table = (gcnew System::Windows::Forms::DataGridView());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->опцииToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->показатьТаблицуToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->справкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->result_field = (gcnew System::Windows::Forms::TextBox());
			this->start_btn = (gcnew System::Windows::Forms::Button());
			this->login = (gcnew System::Windows::Forms::TextBox());
			this->pwd = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->auth_btn = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->db_select = (gcnew System::Windows::Forms::DataGridView());
			this->load_list_btn = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->save_btn = (gcnew System::Windows::Forms::Button());
			this->save_csv_field = (gcnew System::Windows::Forms::TextBox());
			this->save_db_csv_field = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->db_table))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->db_select))->BeginInit();
			this->SuspendLayout();
			// 
			// param_btn
			// 
			this->param_btn->BackColor = System::Drawing::Color::Aqua;
			this->param_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->param_btn->Enabled = false;
			this->param_btn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->param_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightBlue;
			this->param_btn->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->param_btn->Location = System::Drawing::Point(24, 100);
			this->param_btn->Name = L"param_btn";
			this->param_btn->Size = System::Drawing::Size(178, 55);
			this->param_btn->TabIndex = 0;
			this->param_btn->Text = L"Загрузить БД";
			this->param_btn->UseVisualStyleBackColor = false;
			this->param_btn->Click += gcnew System::EventHandler(this, &MyForm::param_btn_Click);
			// 
			// db_table
			// 
			this->db_table->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::ColumnHeader;
			this->db_table->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->db_table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->db_table->Location = System::Drawing::Point(228, 31);
			this->db_table->Name = L"db_table";
			this->db_table->RowHeadersWidth = 20;
			this->db_table->RowTemplate->Height = 24;
			this->db_table->Size = System::Drawing::Size(999, 611);
			this->db_table->TabIndex = 2;
			this->db_table->Visible = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::Aqua;
			this->menuStrip1->Enabled = false;
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->опцииToolStripMenuItem,
					this->справкаToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1227, 31);
			this->menuStrip1->TabIndex = 3;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// опцииToolStripMenuItem
			// 
			this->опцииToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->показатьТаблицуToolStripMenuItem });
			this->опцииToolStripMenuItem->Name = L"опцииToolStripMenuItem";
			this->опцииToolStripMenuItem->Size = System::Drawing::Size(81, 27);
			this->опцииToolStripMenuItem->Text = L"Опции";
			// 
			// показатьТаблицуToolStripMenuItem
			// 
			this->показатьТаблицуToolStripMenuItem->Name = L"показатьТаблицуToolStripMenuItem";
			this->показатьТаблицуToolStripMenuItem->Size = System::Drawing::Size(237, 28);
			this->показатьТаблицуToolStripMenuItem->Text = L"Показать таблицу";
			this->показатьТаблицуToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::показатьТаблицуToolStripMenuItem_Click);
			// 
			// справкаToolStripMenuItem
			// 
			this->справкаToolStripMenuItem->Name = L"справкаToolStripMenuItem";
			this->справкаToolStripMenuItem->Size = System::Drawing::Size(92, 27);
			this->справкаToolStripMenuItem->Text = L"Справка";
			this->справкаToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::справкаToolStripMenuItem_Click);
			// 
			// result_field
			// 
			this->result_field->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->result_field->Enabled = false;
			this->result_field->Location = System::Drawing::Point(228, 40);
			this->result_field->Multiline = true;
			this->result_field->Name = L"result_field";
			this->result_field->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->result_field->Size = System::Drawing::Size(999, 602);
			this->result_field->TabIndex = 4;
			// 
			// start_btn
			// 
			this->start_btn->BackColor = System::Drawing::Color::Aqua;
			this->start_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->start_btn->Enabled = false;
			this->start_btn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->start_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightBlue;
			this->start_btn->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10));
			this->start_btn->Location = System::Drawing::Point(24, 161);
			this->start_btn->Name = L"start_btn";
			this->start_btn->Size = System::Drawing::Size(178, 59);
			this->start_btn->TabIndex = 17;
			this->start_btn->Text = L"Запуск алгоритма";
			this->start_btn->UseVisualStyleBackColor = false;
			this->start_btn->Visible = false;
			this->start_btn->Click += gcnew System::EventHandler(this, &MyForm::start_btn_Click);
			// 
			// login
			// 
			this->login->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->login->Location = System::Drawing::Point(80, 106);
			this->login->Name = L"login";
			this->login->Size = System::Drawing::Size(159, 30);
			this->login->TabIndex = 18;
			// 
			// pwd
			// 
			this->pwd->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->pwd->Location = System::Drawing::Point(80, 172);
			this->pwd->Name = L"pwd";
			this->pwd->Size = System::Drawing::Size(159, 30);
			this->pwd->TabIndex = 19;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label1->Location = System::Drawing::Point(76, 79);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(159, 23);
			this->label1->TabIndex = 20;
			this->label1->Text = L"Имя пользователя:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(255)));
			this->label2->Location = System::Drawing::Point(76, 146);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 23);
			this->label2->TabIndex = 21;
			this->label2->Text = L"Пароль:";
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::Navy;
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Controls->Add(this->auth_btn);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->login);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->pwd);
			this->panel1->Location = System::Drawing::Point(472, 203);
			this->panel1->Margin = System::Windows::Forms::Padding(30, 3, 3, 3);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(321, 289);
			this->panel1->TabIndex = 23;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(321, 73);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 24;
			this->pictureBox1->TabStop = false;
			// 
			// auth_btn
			// 
			this->auth_btn->BackColor = System::Drawing::Color::Aqua;
			this->auth_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->auth_btn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->auth_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightBlue;
			this->auth_btn->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->auth_btn->Location = System::Drawing::Point(80, 217);
			this->auth_btn->Name = L"auth_btn";
			this->auth_btn->Size = System::Drawing::Size(159, 42);
			this->auth_btn->TabIndex = 23;
			this->auth_btn->Text = L"ВХОД";
			this->auth_btn->UseVisualStyleBackColor = false;
			this->auth_btn->Click += gcnew System::EventHandler(this, &MyForm::auth_btn_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// db_select
			// 
			this->db_select->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->db_select->BackgroundColor = System::Drawing::Color::Navy;
			this->db_select->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->db_select->Enabled = false;
			this->db_select->Location = System::Drawing::Point(26, 287);
			this->db_select->MultiSelect = false;
			this->db_select->Name = L"db_select";
			this->db_select->ReadOnly = true;
			this->db_select->RowHeadersVisible = false;
			this->db_select->RowHeadersWidth = 51;
			this->db_select->RowTemplate->Height = 24;
			this->db_select->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->db_select->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
			this->db_select->Size = System::Drawing::Size(178, 342);
			this->db_select->TabIndex = 24;
			this->db_select->Visible = false;
			// 
			// load_list_btn
			// 
			this->load_list_btn->BackColor = System::Drawing::Color::Aqua;
			this->load_list_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->load_list_btn->Enabled = false;
			this->load_list_btn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->load_list_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightBlue;
			this->load_list_btn->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->load_list_btn->Location = System::Drawing::Point(24, 40);
			this->load_list_btn->Name = L"load_list_btn";
			this->load_list_btn->Size = System::Drawing::Size(180, 54);
			this->load_list_btn->TabIndex = 25;
			this->load_list_btn->Text = L"Загрузить список источников";
			this->load_list_btn->UseVisualStyleBackColor = false;
			this->load_list_btn->Click += gcnew System::EventHandler(this, &MyForm::load_list_btn_Click);
			// 
			// save_btn
			// 
			this->save_btn->BackColor = System::Drawing::Color::Aqua;
			this->save_btn->Cursor = System::Windows::Forms::Cursors::Hand;
			this->save_btn->Enabled = false;
			this->save_btn->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->save_btn->FlatAppearance->MouseDownBackColor = System::Drawing::Color::LightBlue;
			this->save_btn->Font = (gcnew System::Drawing::Font(L"Palatino Linotype", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->save_btn->Location = System::Drawing::Point(24, 226);
			this->save_btn->Name = L"save_btn";
			this->save_btn->Size = System::Drawing::Size(179, 55);
			this->save_btn->TabIndex = 26;
			this->save_btn->Text = L"Сохранить";
			this->save_btn->UseVisualStyleBackColor = false;
			this->save_btn->Visible = false;
			this->save_btn->Click += gcnew System::EventHandler(this, &MyForm::save_btn_Click);
			// 
			// save_csv_field
			// 
			this->save_csv_field->Location = System::Drawing::Point(228, 40);
			this->save_csv_field->Multiline = true;
			this->save_csv_field->Name = L"save_csv_field";
			this->save_csv_field->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->save_csv_field->Size = System::Drawing::Size(174, 72);
			this->save_csv_field->TabIndex = 28;
			this->save_csv_field->Visible = false;
			// 
			// save_db_csv_field
			// 
			this->save_db_csv_field->Location = System::Drawing::Point(397, 40);
			this->save_db_csv_field->Multiline = true;
			this->save_db_csv_field->Name = L"save_db_csv_field";
			this->save_db_csv_field->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->save_db_csv_field->Size = System::Drawing::Size(173, 72);
			this->save_db_csv_field->TabIndex = 29;
			this->save_db_csv_field->Visible = false;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Navy;
			this->ClientSize = System::Drawing::Size(1227, 641);
			this->Controls->Add(this->save_db_csv_field);
			this->Controls->Add(this->save_csv_field);
			this->Controls->Add(this->save_btn);
			this->Controls->Add(this->load_list_btn);
			this->Controls->Add(this->db_select);
			this->Controls->Add(this->param_btn);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->start_btn);
			this->Controls->Add(this->result_field);
			this->Controls->Add(this->db_table);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SKYGEN ";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->db_table))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->db_select))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	std::vector<std::vector<int>> ReadDataGridView(DataGridView^ dgv) {
			std::vector<std::vector<int>> result;

			// Пройтись по строкам DataGridView
			for (int i = 0; i < dgv->Rows->Count - 1; ++i) {  // исключаем последнюю строку,
															  // которая используется для добавления новых данных
				DataGridViewRow^ row = dgv->Rows[i];
				std::vector<int> rowData;

				// Пройтись по ячейкам строки, исключая последний столбец
				for (int j = 0; j < row->Cells->Count; ++j) {  // исключаем последний столбец
					int value;
					// Проверяем, есть ли значение в ячейке
					if (row->Cells[j]->Value != nullptr && int::TryParse(row->Cells[j]->Value->ToString(), value)) {
						rowData.push_back(value);  // добавляем значение в строку
						save_db_csv_field->AppendText(value.ToString());
						save_db_csv_field->AppendText(";");
					}
					else {
						rowData.push_back(0); // Если значения в ячейке нет, заполняем ее значением 0
						save_db_csv_field->AppendText("0;");
					}
				}

				result.push_back(rowData);  // добавляем строку в общий результат
				save_db_csv_field->AppendText("\r\n");
			}
			return result;
		}

	private: System::Void param_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		
		String^ uid = login->Text;
		String^ password = pwd->Text;

		
		if (db_select->SelectedCells->Count > 0) {
		
			int selectedRowIndex = db_select->SelectedCells[0]->RowIndex;
			int selectedColumnIndex = db_select->SelectedCells[0]->ColumnIndex;
			
		
			Object^ cellValue = db_select->Rows[selectedRowIndex]->Cells[selectedColumnIndex]->Value;

		
			selected_db = cellValue != nullptr ? cellValue->ToString() : nullptr;
			if (selected_db == "" || selected_db == nullptr || selected_db == " ")
			{
				MessageBox::Show("Выберите таблицу для загрузки!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
			String^ query = "SELECT * FROM ";
			query += selected_db;
			query += ";";
			if (uid == "" || password == "")
			{
				MessageBox::Show("Введите данные для входа!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			else {
				LoadData(uid, password, query, db_table);
			}
			if (db_table->Visible == false)
			{
				db_table->Visible = true;
				result_field->Visible = false;
				показатьТаблицуToolStripMenuItem->Text = "Скрыть таблицу";
			}
			start_btn->Visible = true;
		}
		else
		{
			MessageBox::Show("Выберите таблицу для загрузки!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		
	}
	
	private: System::Void LoadData(String^ login, String^ pwd, String^ query, DataGridView^ table) {
		// Строка подключения к вашей базе данных
		String^ connectionString = "Data Source=dinislampc;Initial Catalog=wind_db;UID=";
		connectionString += login;
		connectionString += ";PWD=";
		connectionString += pwd;
		connectionString += ";";
		// Создание подключения
		SqlConnection^ connection = gcnew SqlConnection(connectionString);

		try {
			connection->Open(); // Открытие подключения

			// SQL-запрос
			
			SqlCommand^ command = gcnew SqlCommand(query, connection);

			// Заполнение DataTable
			SqlDataAdapter^ adapter = gcnew SqlDataAdapter(command);
			DataTable^ dataTable = gcnew DataTable();
			adapter->Fill(dataTable);

			// Привязка данных к DataGridView
			table->DataSource = dataTable;
			

		}	
		catch (Exception^ ex) {
			MessageBox::Show(ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally {
			
			connection->Close(); // Закрытие подключения

		}
	}
	private: System::Void показатьТаблицуToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (db_table->Visible == false)
		{
			db_table->Visible = true;
			result_field->Visible = false;
			показатьТаблицуToolStripMenuItem->Text = "Скрыть таблицу";
		}
		else
		{
			db_table->Visible = false;
			result_field->Visible = true;
			показатьТаблицуToolStripMenuItem->Text = "Показать таблицу";
		}
	}
	
	private: System::Void start_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		// Очищаем текстовое поле перед выводом
		result_field->Text = "";
		

		vector<vector<int>> data = ReadDataGridView(db_table);
		if (db_table->Visible == true)
		{
			db_table->Visible = false;
			result_field->Visible = true;
			показатьТаблицуToolStripMenuItem->Text = "Показать таблицу";
		}
		
		
		// Начало замера времени
		auto start = std::chrono::high_resolution_clock::now();
		auto G = create_wind_turbine_graph();
		auto result = genetic_algorithm(G, POPULATION_SIZE, NUM_GENERATIONS, TOURNAMENT_SIZE, MUTATION_RATE, data);
		auto end = std::chrono::high_resolution_clock::now();
		for (int i = 1; i < result.first.size(); ++i) {
			// Формируем строку с результатами
			
			String^ output = String::Format(
				"---------------------------------------------\r\n"
				"Node {0}\r\n"
				"ID: {1}\r\n"
				"Лопасть 1 (коррозия): {2}\r\n"
				"Лопасть 2 (коррозия): {3}\r\n"
				"Лопасть 3 (коррозия): {4}\r\n"
				"Лопасть 1 (мех. повреждения): {5}\r\n"
				"Лопасть 2 (мех. повреждений): {6}\r\n"
				"Лопасть 3 (мех. повреждений): {7}\r\n"
				"Лопасть 1 (обледенение): {8}\r\n"
				"Лопасть 2 (обледенение): {9}\r\n"
				"Лопасть 3 (обледенение): {10}\r\n"
				"Лопасть 1 (эрозия): {11}\r\n"
				"Лопасть 2 (эрозия): {12}\r\n"
				"Лопасть 3 (эрозия): {13}\r\n"
				"Ротор (коррозия): {14}\r\n"
				"Ротор (мех. повреждения): {15}\r\n"
				"Ротор (обледенение): {16}\r\n"
				"Гондола (коррозия): {17}\r\n"
				"Гондола (мех. повреждения): {18}\r\n"
				"Мачта (коррозия): {19}\r\n"
				"Мачта (мех. повреждения): {20}\r\n"
				"Состояние генератора: {21}\r\n"
				"Состояние датчиков: {22}\r\n"
				"Состояние электроники: {23}\r\n"
				"---------------------------------------------\r\n",
				i,
				result.first[i].id,
				result.first[i].blade1_corr,
				result.first[i].blade2_corr,
				result.first[i].blade3_corr,
				result.first[i].blade1_md,
				result.first[i].blade2_md,
				result.first[i].blade3_md,
				result.first[i].blade1_ice,
				result.first[i].blade2_ice,
				result.first[i].blade3_ice,
				result.first[i].blade1_err,
				result.first[i].blade2_err,
				result.first[i].blade3_err,
				result.first[i].rotor_corr,
				result.first[i].rotor_md,
				result.first[i].rotor_ice,
				result.first[i].gondola_corr,
				result.first[i].gondola_md,
				result.first[i].mast_corr,
				result.first[i].mast_md,
				result.first[i].generator_cond,
				result.first[i].sensors_cond,
				result.first[i].electronics_cond
			);

			// Добавляем результат в текстовое поле
			result_field->AppendText(output);
		}

		//Формируем вывод для .csv
		for (int i = 1; i < result.first.size(); ++i) {
			// Формируем строку с результатами

			String^ output = String::Format(
				"{0};"
				"{1};"
				"{2};"
				"{3};"
				"{4};"
				"{5};"
				"{6};"
				"{7};"
				"{8};"
				"{9};"
				"{10};"
				"{11};"
				"{12};"
				"{13};"
				"{14};"
				"{15};"
				"{16};"
				"{17};"
				"{18};"
				"{19};"
				"{20};"
				"{21};"
				"{22};\r\n",
				result.first[i].id,
				result.first[i].blade1_corr,
				result.first[i].blade2_corr,
				result.first[i].blade3_corr,
				result.first[i].blade1_md,
				result.first[i].blade2_md,
				result.first[i].blade3_md,
				result.first[i].blade1_ice,
				result.first[i].blade2_ice,
				result.first[i].blade3_ice,
				result.first[i].blade1_err,
				result.first[i].blade2_err,
				result.first[i].blade3_err,
				result.first[i].rotor_corr,
				result.first[i].rotor_md,
				result.first[i].rotor_ice,
				result.first[i].gondola_corr,
				result.first[i].gondola_md,
				result.first[i].mast_corr,
				result.first[i].mast_md,
				result.first[i].generator_cond,
				result.first[i].sensors_cond,
				result.first[i].electronics_cond
			);

			// Добавляем результат в текстовое поле
			save_csv_field->AppendText(output);
		}


		// Вычисляем продолжительность
		std::chrono::duration<double> duration = end - start;
		String^ bestIndividualOutput = String::Format("Best individual: {0}\r\n", result.second);
		String^ durationOutput = String::Format("Время выполнения: {0} секунд\r\n", duration.count());

		// Добавляем информацию о лучшем индивидууме и времени выполнения
		result_field->AppendText(bestIndividualOutput);
		result_field->AppendText(durationOutput);

		save_btn->Visible = true;
		save_btn->Enabled = true;
	}
	private: System::Void auth_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ uid = login->Text;
		String^ password = pwd->Text;
		
		if (uid == "" || password == "")
		{
			MessageBox::Show("Введите данные для входа!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (uid != "User1" && password != "sa")
		{
			MessageBox::Show("Неверное имя пользователя или пароль!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			panel1->Visible = false;
			menuStrip1->Enabled = true;
			result_field->Enabled = true;
			start_btn->Enabled = true;
			db_select->Enabled = true;
			load_list_btn->Enabled = true;
			param_btn->Enabled = true;
		}
	}
	
	private: System::Void load_list_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ query = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE = 'BASE TABLE';";
		db_select->Visible = true;
		LoadData("User1", "sa", query, db_select);
	}
	private: System::Void справкаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (result_field->Text != "") result_field->Text = "";
		if (db_table->Visible == true)
		{
			db_table->Visible = false;
			result_field->Visible = true;
			показатьТаблицуToolStripMenuItem->Text = "Показать таблицу";
		}

		String^ manual = String::Format(
			"Порядок выполнения программы:\r\n"
			"1. Нажать кнопку <Загрузить список источников>;\r\n"
			"2. Выбрать название одной из таблиц в появившемся окне\r\n"
			"3. Нажать кнопку <Загрузить БД>;\r\n"
			"4. Нажать кнопку <Запуск алгоритма>;\r\n"
			"5. При необходимости нажать кнопку <Сохранить результат> и выбрать папку сохранения;\r\n"
		);

		result_field->Text = manual;
	}
	private: System::Void save_btn_Click(System::Object^ sender, System::EventArgs^ e) {
		
		if (result_field->Text != "" && save_db_csv_field->Text != "" && save_csv_field->Text != "") {
			String^ file1;
			String^ file2;
			String^ file3;

			for (int i = 0; i < 3; i++)
			{
				switch (i)
				{
				case 0:
				{
					saveFileDialog1->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*"; // Устанавливаем фильтр для файлов
					saveFileDialog1->Title = "Сохранить вывод как";

					if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
						// Получаем путь к файлу
						file1 = saveFileDialog1->FileName;
					}
				}
				break;
				case 1:
				{
					saveFileDialog1->Filter = "CSV files (*.csv)|*.csv|All files (*.*)|*.*"; // Устанавливаем фильтр для файлов
					saveFileDialog1->Title = "Сохранить результат как";
					
					if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
						// Получаем путь к файлу
						file2 = saveFileDialog1->FileName;
					}
				}
				break;
				case 2:
				{
					saveFileDialog1->Filter = "CSV files (*.csv)|*.csv|All files (*.*)|*.*"; // Устанавливаем фильтр для файлов
					saveFileDialog1->Title = "Сохранить таблицу как";

					if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
						// Получаем путь к файлу
						file3 = saveFileDialog1->FileName;
					}
				}
				break;
				default:
					break;
				}
				// Показываем диалог и проверяем, была ли нажата кнопка "Сохранить"
			}
			//// Сохраняем текст из TextBox в файл
			System::IO::File::WriteAllText(file1, result_field->Text);
			System::IO::File::WriteAllText(file2, save_csv_field->Text);
			System::IO::File::WriteAllText(file3, save_db_csv_field->Text);
			// Выводим сообщение о успешном сохранении (по желанию)
			MessageBox::Show("Файлы успешно сохранены!", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("Результат для сохранения отсутствует!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		
	}

};
}
