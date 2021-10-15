#include <tuple>
#include <utility>
#include <commands/command.h>
#include <instructions/instruction_ids.h>


class get_command_t : public producer_command_t {
public:
    auto execute(std::tuple<>, std::tuple<>) {
        return std::make_tuple(&m_data, sizeof(m_data), false);
    }

private:
    inline static uint8_t m_data[] = {
        0x07,   // Packet length - 1.
        0x10,   // Version.
        // Supported instructions.
        instruction_ids_t::get,
        instruction_ids_t::get_ver_and_rps,
        instruction_ids_t::get_id,
        instruction_ids_t::read_memory,
        instruction_ids_t::go,
        instruction_ids_t::write_memory,
        instruction_ids_t::erase_memory
    };
};
