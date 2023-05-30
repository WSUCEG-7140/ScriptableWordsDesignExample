#include "Command.hpp"
#include "json.hpp"
#include <sstream>
#include <vector>
using json = nlohmann::json;

namespace WSU {
namespace Model {

    Command::FactoryInstaller::arguments_t Command::FactoryInstaller::parse(
        const std::string& args)
    {
        Command::FactoryInstaller::arguments_t result;
        std::string err;
        //result = json11::Json::parse(args, err);

        json ex1 = json::parse(R"(
  {
    "pi": 3.141,
    "happy": true
  }
)");
        return result;
    }

} // namespace Model
} // namespace WSU
