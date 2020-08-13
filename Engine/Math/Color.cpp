#include "pch.h"
#include "Color (2).h"
#include <string>



namespace nc
{
	const Color Color::white{ 1,1,1 };
	const Color Color::red{ 1,0,0 };
	const Color Color::green{ 0,1,0 };
	const Color Color::blue{ 0,1,2 };

	std::istream& operator >> (std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		if (line.find("{") != std::string::npos)
		if (line.find("{") != std::string::npos)
		if (line.find("{") != std::string::npos)
		{
			std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
			c.r = std::stof(cr);

			line = line.substr(line.find(",")+1, line.find("}") - line.find(","));

			std::string cg = line.substr(0, line.find(","));
			c.g = std::stof(cg);

			std::string cb = line.substr(line.find("," + 1),line.find("}")-line.find(",")-1);
			c.b = std::stof(cb);
		}

		return stream;
	};

	std::ostream& operator<<(std::ostream& stream, Color& c)
	{
		stream << c.r << " " << c.g << " " << c.b << " " << c.a;

		return stream;
	}

};


