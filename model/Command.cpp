#include "Command.hpp"
//#include "json.hpp"
#include <sstream>
#include <vector>
//using json = nlohmann::json;

namespace WSU {
namespace Model {

    Command::FactoryInstaller::arguments_t Command::FactoryInstaller::parse(
        const std::string& args)
    {
        return Command::FactoryInstaller::arguments_t { args };
    }

} // namespace Model
} // namespace WSU
