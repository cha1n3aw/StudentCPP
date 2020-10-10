#include <iostream>
#include <fstream> 
#include <ctime> 

using namespace std; 

char* merge_strings(char* first_string, const char* second_string);
char* duplicate_strings(const char* income);
char* get_current_time();

class file_write 
{
	int id; 
	int executions = 0; 
	int path;
	char* name;
	char* date;
	const char* type;
	char* body; 
public:
	file_write(int id, char* name, unsigned int executions, int path, const char* type, char* date, char* body) 
	{
		this->id = id; 
		this->name = name; 
		this->executions = executions; 
		this->path = path; 
		this->type = type; 
		this->date = date; 
		this->body = body; 
	}
	file_write(const file_write& copy)
	{
		this->id = copy.id;
		this->executions = copy.executions;
		this->name = copy.name;
		this->path = copy.path;
		this->type = copy.type;
		this->date = copy.date;
		this->body = copy.body;
	}
	
	file_write() {} 

	int call_id() { return id; } 
	int call_executions() { return executions; }
	int call_path() { return path; }
	char* call_name() { return  name; }
	const char* call_type() { return type; }
	char* call_date() { return date; }
	char* call_body() { return body; }
	
	friend ostream& operator << (ostream& output, file_write data) 
	{
		output << data.call_id() << '\t' << data.call_type() << '\t' << data.call_name() << '\t' << data.call_date() << '\t' << data.call_executions();
		return output;
	}
};

template<typename template_key, typename template_value> 
class collection
{
	class collection_element 
	{
	public:
		template_key key; 
		template_value value;
		collection_element(template_key key, template_value value)
		{
			this->key = key; 
			this->value = value;
		}
		collection_element() {} 
	};

	unsigned int collection_size = 0; 
	collection_element **array; 

	void increase_array() 
	{
		collection_element **new_array = new collection_element *[collection_size + 1]; 
		for (int i = 0; i < collection_size; i++) new_array[i] = array[i];
		array = new_array;
	}
	void decrease_array() 
	{
		collection_element** new_array = new collection_element *[collection_size - 1]; 
		for (int i = 0; i < collection_size - 1; i++) new_array[i] = array[i]; 
		array = new_array;
	}

public:
	collection()
	{
		collection_size = 0; 
		array = new collection_element *[collection_size];
		for (int i = 0; i < collection_size; i++)
		{
			array[i] = new collection_element();
		}
	}

	void value_set(template_value value, template_key key)
	{
		for (int i = 0; i < collection_size; i++)
		{
			if (key == array[i]->key) array[i]->value = value;
		}
	}

	void add_key_value(template_key key, template_value value)
	{
		increase_array();
		array[collection_size] = new collection_element(key, value); 
		collection_size++;
	}

	void delete_by_key(template_key key)
	{
		for (int i = 0; i < collection_size; i++)
		{
			if (array[i]->key == key)
			{
				swap_keys(i, collection_size - 1);
				decrease_array();
				collection_size--;
			}
		}
	}

	void swap_keys(int first, int second)
	{
		collection_element *temp_array = array[first];
		array[first] = array[second];
		array[second] = temp_array;
	}

	template_value key_search(template_key key)
	{
		for (int i = 0; i < collection_size; i++)
		{
			if (key == array[i]->key) return array[i]->value;
		}
	}

	int call_collection_size() { return collection_size; } 

	friend ostream& operator << (ostream& out, collection inst) 
	{
		for (int i = 0; i < inst.call_collection_size(); i++)
		{
			out << inst.key_search(i) << endl;
		}
		return out;
	}
	friend istream& operator >> (istream& input, collection& inst) 
	{
		while (input.peek() != EOF)
		{
			template_key key;
			template_value* value = new template_value;
			input >> key;
			input >> *value;
			inst.add_key_value(key, *value); 
		}
		return input;
	}
};

class FS 
{
	collection<int, file_write> *call_collection; 
	int file_count;
public:
	FS()
	{
		file_count = 0;
		call_collection = new collection<int, file_write>;
	}
	FS(const FS& copy_FS)
	{
		this->file_count = copy_FS.file_count;
		this->call_collection = copy_FS.call_collection;
	}
	int return_file_count()
	{
		return file_count;
	}
	void state_file_count(int file_count)
	{
		this->file_count = file_count;
	}
	FS* get_prev_array(int id, FS *fs)
	{
		FS *arr = new FS();
		for (int i = 0; i < fs->return_file_count(); i++)
		{
			if (fs->call_collection->key_search(i).call_path() == id)
			{
				file_write *record = new file_write(fs->call_collection->key_search(i).call_id(), fs->call_collection->key_search(i).call_name(), fs->call_collection->key_search(i).call_executions(),
				fs->call_collection->key_search(i).call_path(), fs->call_collection->key_search(i).call_type(), fs->call_collection->key_search(i).call_date(), fs->call_collection->key_search(i).call_body());
				arr->add_id(i, *record);
			}
		}
		return arr;
	}
	collection<int, file_write> call_array()
	{
		return *call_collection;
	}
	void add_id(int id, file_write record)
	{
		call_collection->add_key_value(id, record);
		file_count++;
	}

	void delete_id(int id)
	{
		call_collection->delete_by_key(id);
	}

	void save()
	{
		ofstream fout("log.txt");
		for (int i = 0; i < file_count; i++)
		{
			fout << call_collection->key_search(i).call_id() << "|"	<< call_collection->key_search(i).call_type() << "|" << call_collection->key_search(i).call_name() << "|"
				<< call_collection->key_search(i).call_executions() << "|" << call_collection->key_search(i).call_path() << "|" << call_collection->key_search(i).call_date() << "|"
				<< call_collection->key_search(i).call_body() << '\0' << endl;
		}
	}
	int get_id_by_name(char* name)
	{
		for (int i = 0; i < this->file_count; i++)
		{
			if (!strcmp(this->call_collection->key_search(i).call_name(), name))
				return this->call_collection->key_search(i).call_id();
		}
	}
	int get_id(char* buffer)
	{
		int count = 0;
		for (int i = 0; i <= strlen(buffer); i++)
		{
			if (buffer[i] == '\\' || buffer[i] == '\0')
				count++;
		}
		char** arr = new char*[count];
		for (int g = 0; g < count; g++)
		{
			arr[g] = new char[256];
		}
		int temp_id = 0;
		int i = 0;
		for (int j = 0; j < count; j++)
		{
			char*  temp = new char[256];
			for (i; i < strlen(buffer) + 1; i++)
			{
				if (buffer[i] != '\\' || buffer[i] == '\0')
				{
					temp[temp_id] = buffer[i];
					temp_id++;
				}
				else
				{
					temp[temp_id] = '\0';
					temp_id = 0;
					break;
				}
			}
			i++;
			arr[j] = temp;
		}
		if (count == 1) return 0;
		int id = get_id_by_name(arr[0]);
		FS *childs = new FS();
		for (int f = 1; f < count; f++)
		{
			childs = get_prev_array(id, this);
			for (int j = 1; j < childs->file_count; j++)
			{
				if (!strcmp(arr[f], childs->call_collection->key_search(j).call_name()))
				{
					id = get_id_by_name(childs->call_collection->key_search(j).call_name());
				}
			}
		}
		return id;
	}

	bool load_previous()
	{
		ifstream fout("log.txt");
		if (fout.is_open())
		{
			char* buffer = new char[256];
			int flag = 0;
			while (!fout.eof())
			{
				fout.getline(buffer, 256);
				char* prev_id = new char[5];
				char* type = new char[10];
				char* name = new char[256];
				char* executions = new char[64];
				char* date = new char[20];
				char* id = new char[5];
				char* body = new char[256];
				if (strcmp(buffer, "") != 0)
				{
					char* temp_string = new char[80];
					int temp_id = 0;
					for (int i = 0; i < strlen(buffer) + 1; i++)
					{
						if (buffer[i] != '|')
						{
							temp_string[temp_id] = buffer[i];
							temp_id++;
						}
						else
						{
							temp_string[temp_id] = '\0';
							if (flag == 0)
							{
								id = new char[strlen(temp_string) + 1];
								id = duplicate_strings(temp_string);
								flag = 1;
								temp_id = 0;
								continue;
							}
							if (flag == 1)
							{
								type = new char[strlen(temp_string) + 1];
								type = duplicate_strings(temp_string);
								flag = 2;
								temp_id = 0;
								continue;
							}
							if (flag == 2)
							{
								name = new char[strlen(temp_string) + 1];
								name = duplicate_strings(temp_string);
								flag = 3;
								temp_id = 0;
								continue;
							}
							if (flag == 3)
							{
								executions = new char[strlen(temp_string) + 1];
								executions = duplicate_strings(temp_string);
								flag = 4;
								temp_id = 0;
								continue;
							}
							if (flag == 4)
							{
								prev_id = new char[strlen(temp_string) + 1];
								prev_id = duplicate_strings(temp_string);
								flag = 5;
								temp_id = 0;
								continue;
							}
							if (flag == 5)
							{

								date = new char[strlen(temp_string) + 1];
								date = duplicate_strings(temp_string);
								temp_id = 0;
								continue;
							}
						}
						if (buffer[i] == '\0')
						{
							body = new char[strlen(temp_string) + 1];
							body = duplicate_strings(temp_string);
							file_write *record = new file_write(atoi(id), name, atoi(executions), atoi(prev_id), type, date, body);
							this->call_collection->add_key_value(file_count, *record);
							file_count++;
							temp_id = 0;
							flag = 0;
							break;
						}
						
					}
				}
			}
			return true;
		}
		else
			cout << "log.txt создан" << endl;

		return false;
	}
	file_write* max_file_calls()
	{
		file_write *tmp = new file_write;
		for (int i = 0; i < this->return_file_count(); i++)
		{
			if (this->call_array().key_search(i).call_executions() > tmp->call_executions())
				*tmp = this->call_array().key_search(i);
		}
		return tmp;
	}
};

int main()
{
	FS *fs = new FS;
	file_write *tmp;
	FS *fstmp = new FS;
	bool result = fs->load_previous();
	if (!result)
	{
		ofstream fout("log.txt");
		char* name;
		name = duplicate_strings("C:\\\\");
		tmp = new file_write(0, name, 0, -1, duplicate_strings("Folder"), get_current_time(), duplicate_strings(" "));
		fs->add_id(0, *tmp);
		fs->save();
	}
	while (1)
	{
		int dcs;
		int size;
		int prev_id = 0;
		char dcs1;
		char dcs2;
		char* filename = new char[512];
		char* path = new char[512];
		char* body = new char[512];
		char* deletion_date = new char[512];
		cout << "1) Создать каталог" << endl << "2) Создать файл" << endl << "3) Вывести содержимое каталога" << endl << "4) Самый популярный файл" << endl 
			 << "5) Открыть и изменить файл" << endl << "6) Удалить файл или папку по дате" << endl << "7) Сохранить и выйти" << endl;
		cin >> dcs;
		switch (dcs)
		{
		case 1:
			cout << "Введите путь: ";
			cin >> path;
			prev_id = fs->get_id(path);
			cout << "Введите имя папки: ";
			cin >> filename;
			tmp = new file_write(fs->return_file_count(), duplicate_strings(filename), 0, prev_id, duplicate_strings("Folder"), get_current_time(), duplicate_strings(""));
			fs->add_id(fs->return_file_count(), *tmp);
			fs->save(); 
			break;
		case 2:
			cout << "Введите путь: ";
			cin >> path;
			prev_id = fs->get_id(path);
			cout << "Введите имя файла: ";
			cin >> filename;
			tmp = new file_write(fs->return_file_count(), duplicate_strings(filename), 0, prev_id, duplicate_strings("File"), get_current_time(), duplicate_strings(""));
			fs->add_id(fs->return_file_count(), *tmp);
			fs->save(); 
			break;
		case 3:
			cout << "ID" << '\t' << "Тип" << '\t' << "Имя" << '\t' << '\t' << '\t' << "Дата" << '\t' << '\t' << '\t' << "Кол-во посещений" << endl;
			cout << fs->call_array() << endl;
			break;
		case 4:
			cout << fs->max_file_calls() << endl;
			break;
		case 5:
			cout << "Введите путь и название: ";
			cin >> path;
			prev_id = fs->get_id(path);
			if (!strcmp(fs->call_array().key_search(prev_id).call_type(), "Folder"))
			{

				fstmp = fs->get_prev_array(prev_id, fs);
				cout << fstmp->call_array() << endl;
			}
			else
			{
				cout << "Содержимое файла: ";
				cout << fs->call_array().key_search(prev_id).call_body() << endl;
				cout << "Отредактировать содержимое? Y/N" << endl;
				cin >> dcs1;
				while (dcs1 != 'Y' && dcs1 != 'y' && dcs1 != 'N' && dcs1 != 'n')
				{
					cout << "Неверный ответ!" << endl;
					cin.clear();
					cin.ignore(9999999, '\n');
					cin >> dcs1;
				}
				if (dcs1 == 'Y' || dcs1 == 'y')
				{
					cin >> body;
					tmp = new file_write(fs->call_array().key_search(prev_id).call_id(), fs->call_array().key_search(prev_id).call_name(), fs->call_array().key_search(prev_id).call_executions() + 1,
					fs->call_array().key_search(prev_id).call_path(), fs->call_array().key_search(prev_id).call_type(), fs->call_array().key_search(prev_id).call_date(), body);
					fs->call_array().value_set(*tmp, prev_id);
					fs->save();
					return 0;
				}
				if (dcs1 == 'N' || dcs1 == 'n')
				{
					tmp = new file_write(fs->call_array().key_search(prev_id).call_id(), fs->call_array().key_search(prev_id).call_name(), fs->call_array().key_search(prev_id).call_executions() + 1,
						fs->call_array().key_search(prev_id).call_path(), fs->call_array().key_search(prev_id).call_type(), fs->call_array().key_search(prev_id).call_date(),
						fs->call_array().key_search(prev_id).call_body()); fs->call_array().value_set(*tmp, prev_id);
					fs->save();
				}
			}
			break;
		case 6:
			cout << "Введите путь к папке, в которой хотите удалить все элементы раньше заданной даты" << endl;
			cin >> path;
			prev_id = fs->get_id(path);
			if (!strcmp(fs->call_array().key_search(prev_id).call_type(), "Folder"))
			{
				fstmp = fs->get_prev_array(prev_id, fs);
				cout << "Введите дату в формате dd.mm.yy_hh:mm:ss" << endl;
				cin >> deletion_date;
				size = fstmp->return_file_count();
				for (int i = 0; i < size; i++)
				{
					dcs1 = strcmp(fstmp->call_array().key_search(i).call_date(), deletion_date);
					if (dcs1 < 0)
					{
						fs->delete_id(fstmp->call_array().key_search(i).call_id());
						size--;
					}

				}
			}
			fs->save();
			break;
		case 7:
			cout << "Вы уверены, что хотите выйти? Y/N" << endl;
			cin >> dcs2;
			while (dcs2 != 'Y' && dcs2 != 'y' && dcs2 != 'N' && dcs2 != 'n') 
			{
				cout << "Неверный ответ!" << endl;
				cin.clear();
				cin.ignore(9999999, '\n');
				cin >> dcs2;
			}
			if (dcs2 == 'Y' || dcs2 == 'y')
			{
				fs->save();
				return 0;
			}
			if (dcs2 == 'N' || dcs2 == 'n')
			{
				fs->save();
				main();
			}
		}
	}
}

char* merge_strings(char* first_string, const char* second_string)
{
	char* tmp_string = new char[strlen(first_string) + strlen(second_string) + 3];
	int i = 0;
	for (i; i <= strlen(first_string); i++)
	{
		tmp_string[i] = first_string[i];
		if (first_string[i] == EOF)
		{
			break;
		}

	}
	cout << endl << endl << endl;
	for (int j = 0; j <= strlen(second_string); j++, i++)
	{
		tmp_string[i - 1] = second_string[j];
	}
	tmp_string[i] = EOF;
	return tmp_string;
}
char* duplicate_strings(const char* income)
{
	char* tmp_string = new char[strlen(income) + 3];
	int i = 0;
	for (i; i < strlen(income) + 1; i++)
	{
		tmp_string[i] = income[i];
	}
	tmp_string[i + 1] = EOF;
	return tmp_string;
}
char* get_current_time()
{
	time_t current_time;
	struct tm* timeinfo;
	char buffer[20];
	time(&current_time);
	timeinfo = localtime(&current_time);
	strftime(buffer, sizeof(buffer), "%d.%m.%Y_%H:%M:%S", timeinfo); 
	char* timestring(buffer);
	return timestring;
}