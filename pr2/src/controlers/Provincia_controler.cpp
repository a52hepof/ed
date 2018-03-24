#include "Provincia_controler.hpp"

void Provincia_controler::load_data(std::string csv_file){
	CSV_reader csv(csv_file);
	CSV_data data=csv.load_csv();
	Provincia provincia;
	Municipio municipio;
	//dumps the data into the class
	for (size_t i = 0; i < data.lines(); i++) {

		Line line=data.get_line(i);

		municipio.set_postal_code(atoi(line.get_field(0).c_str()));
		municipio.set_name(line.get_field(1));
		municipio.set_mens(atoi(line.get_field(2).c_str()));
		municipio.set_womens(atoi(line.get_field(3).c_str()));
		push_municipio(municipio);
	}
	// short_list();
}
