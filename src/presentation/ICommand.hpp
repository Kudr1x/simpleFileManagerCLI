#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <string>

namespace presentation {

    class ICommand {
    public:
        virtual ~ICommand() = default;
        virtual void execute() = 0;
        [[nodiscard]] virtual std::string getName() const = 0;
    };

}

#endif
