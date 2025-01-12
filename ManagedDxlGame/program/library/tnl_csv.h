#pragma once
#include <string>
#include <vector>

namespace tnl {

	class CsvCell {
	public:
		CsvCell(const std::string& s) {
			str_ = s;
			int_ = std::atoi(s.c_str());
			float_ = (float)std::atof(s.c_str());
			bool_ = (s == "TRUE" || s == "true") ? true : false;
		}

		const std::string& getString() const noexcept { return str_; }
		int getInt() const noexcept { return int_; }
		float getFloat() const noexcept { return float_; }
		bool getBool() const noexcept { return bool_; }

	private:
		std::string str_ = "";
		int int_ = 0;
		float float_ = 0;
		bool bool_ = false;
	};

	template<typename T>
	struct CsvTraits;
	template<>
	struct CsvTraits<int> {
		static constexpr auto Name = "int";
		static constexpr int Value = 0;
	};
	template<>
	struct CsvTraits<float> {
		static constexpr auto Name = "float";
		static constexpr int Value = 1;
	};
	template<>
	struct CsvTraits<std::string> {
		static constexpr auto Name = "string";
		static constexpr int Value = 2;
	};
	template<>
	struct CsvTraits<CsvCell> {
		static constexpr auto Name = "CsvCell";
		static constexpr int Value = 3;
	};


	//----------------------------------------------------------------------------------------------
	// Csv Loader
	// arg1... �t�@�C���p�X
	// ret.... �e���v���[�g�w�肳�ꂽ�f�[�^�̂Q�����z��
	// tips... �e���v���[�g�w��ł���͈̂ȉ��̌^
	// ....... int
	// ....... float
	// ....... std::string
	// ....... tnl::CsvCell
	// ....... �e���v���[�g�w����ȗ������ꍇ tnl::CsvCell �ɂȂ�܂�
	template< class T = CsvCell >
	std::vector<std::vector<T>> LoadCsv(const std::string& file_path){
		
		size_t fsize = tnl::GetFileSize(file_path.c_str());
		if (-1LL == fsize) {
			throw std::runtime_error("LoadCsv : file path error");
		}
		char* fbuff = new char[fsize] ;

		FILE* fp = nullptr;
		fopen_s(&fp, file_path.c_str(), "r");
		fread(fbuff, fsize, 1, fp);
		if(fp) fclose(fp);

		std::vector<std::vector<T>> out = LoadCsvFromMemory<T>(fbuff, fsize);

		delete[] fbuff;
		return std::move(out);
	}


	//----------------------------------------------------------------------------------------------
	// �������ɓǂݍ��܂ꂽ csv ��ǂݍ���
	// arg1... csv �����[�h���ꂽ�������A�h���X
	// arg2... �������T�C�Y
	// ret.... �e���v���[�g�w�肳�ꂽ�f�[�^�̂Q�����z��
	// tips... �e���v���[�g�w��ł���͈̂ȉ��̌^
	// ....... int
	// ....... float
	// ....... std::string
	// ....... tnl::CsvCell
	// ....... �e���v���[�g�w����ȗ������ꍇ tnl::CsvCell �ɂȂ�܂�
	template< class T = CsvCell >
	std::vector<std::vector<T>> LoadCsvFromMemory(void* memory, size_t size) {
		std::vector<std::vector<T>> out;
		size_t fsize = size;
		char* fbuff = (char*)(memory);
		std::string file_str(fbuff);
		LoadCsvFromStringBuffer<T>(out, file_str);
		return std::move(out);
	}


	template< class T = CsvCell >
	void LoadCsvFromStringBuffer(std::vector<std::vector<T>>& out, std::string& string_buffer) {

		std::string line;
		while (GetStringLine(line, string_buffer)) {
			std::vector<T> data;

			while (1) {
				size_t c = line.find(",");
				if (c == std::string::npos) {
					c = line.find("\n");
				}
				std::string s = line.substr(0, c);

				if (s.empty()) {
					line = line.substr(c + 1, line.length() - (c + 1));
					if (line.empty() || line == "/n") break;
					continue;
				}

				if constexpr (CsvTraits<int>::Value == CsvTraits<T>::Value) {
					data.emplace_back(std::atoi(s.c_str()));
				}
				if constexpr (CsvTraits<float>::Value == CsvTraits<T>::Value) {
					data.emplace_back((float)std::atof(s.c_str()));
				}
				if constexpr (CsvTraits<std::string>::Value == CsvTraits<T>::Value) {
					data.emplace_back(std::move(s));
				}
				if constexpr (CsvTraits<CsvCell>::Value == CsvTraits<T>::Value) {
					data.emplace_back(CsvCell(s));
				}

				line = line.substr(c + 1, line.length() - (c + 1));
				if (line.empty() || line == "/n") break;
			}
			out.emplace_back(std::move(data));
		}

	}


}

