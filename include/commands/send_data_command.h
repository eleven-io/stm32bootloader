#include <tuple>
#include <utility>
#include <instructions/instruction_ids.h>


template<uint8_t v_address, uint8_t v_length>
class send_data_command_t {
public:
    constexpr static bool is_producer = true;
    constexpr static bool is_consumer = false;
    constexpr static bool is_conditional = false;
    constexpr static bool is_set = false;

    using parameter_indexes = std::index_sequence<0, 1>;
    using buffer_indexes = std::index_sequence<>;

public:
    auto execute(uint32_t address, uint8_t length) {
        return std::make_tuple(address, length, false);
    }
};
