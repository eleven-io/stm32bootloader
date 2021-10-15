#include <cstdint>
#include <utility>



struct dummy_parameters_t {
    using indexes = std::index_sequence<>;
    constexpr static std::size_t size = 0;
};


struct dummy_buffers_t {
    using indexes = std::index_sequence<>;
    constexpr static std::size_t size = 0;
};


template<uint8_t v_cmd_id, class t_commands, class t_parameters = dummy_parameters_t, class t_buffers = dummy_buffers_t>
class instruction_processor_t {
public:
    constexpr static uint8_t instruction_id = v_cmd_id;
    using commands_t = t_commands;
    using paramters_t = t_parameters;
    using buffers_t = t_buffers;
};
