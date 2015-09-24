#include <vector>
#include <boost/algorithm/string.hpp>
namespace myfile
{
typedef std::vector<std::string> stringvector;
stringvector read(const char  filename[]);

void write(const char filename[], const char content[]);

inline void write(const char filename[], std::string content) {
	write(filename, content.c_str());
};

}
