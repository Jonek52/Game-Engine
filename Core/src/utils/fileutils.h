#pragma once

#include <string>

namespace sparky {

	std::string read_file (const char * filepath) {

		FILE* file = fopen (filepath, "rt");
		
		fseek (file, 0, SEEK_END);
		unsigned long lenght = ftell (file);

		char* file_data = new char[lenght + 1];

		memset (file_data, 0, lenght + 1);
		fseek (file, 0, SEEK_SET);
		fread (file_data, 1, lenght, file);
		fclose (file);

		std::string result (file_data);
		delete[] file_data;

		return result;
	}

}