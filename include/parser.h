#pragma once

#include <string>

#include "gcode_program.h"


namespace gcode {

	gcode_program parse_gcode(const std::string& program_text);


	gcode_program parse_gcode_with_char(const char* char_gcode);

	void parseNextN(gcode_program* prog, const char* char_gcode, uint16_t* index, uint8_t nb);

}
