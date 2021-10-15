#include <tuple>
#include <utility>
#include <commands/command.h>
#include <instructions/instruction_ids.h>


class get_id_command_t : public producer_command_t {
public:
    auto execute(std::tuple<>, std::tuple<>) {
        return std::make_tuple(&m_data, sizeof(m_data), false);
    }

private:
    inline static uint8_t m_data[] = {
        0x01,   // Length.
        0x04,   // Version.
        0x10
    };
};
