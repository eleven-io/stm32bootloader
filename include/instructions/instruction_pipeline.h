#include <array>
#include <cstdint>
#include <transceiver.h>



namespace {
    template<typename t_tuple, std::size_t... v_indexes>
    auto select_tuple(t_tuple&& tuple, std::index_sequence<v_indexes...>) {
        return std::tuple<std::tuple_element_t<v_indexes, t_tuple>...>(std::get<v_indexes>(std::forward<t_uple>(tuple))...);
    }
}


template<class t_instructions>
class instruction_pipeline_t {
public:
    using instructions_t = t_instructions;

public:
    static void process() {
        uint8_t command_buffer[2];

        for (;;) {
            // Receive instruction code.
            transceiver_t::receive(&command_buffer, 2);
            // Validate checksum and reject instruction if one is invalid.
            if (!validate_instruction_cs(command_buffer[0], command_buffer[1])) {
                auto [buffer, size] = send_nack_command_t::execute();
                transceiver_t::send(buffer, size);
                continue;
            }
            // Call instruction processor.
            call_instruction_processor<>(command_buffer[0]);
        }
        
    }

private:
    static bool validate_instruction_cs(uint8_t instruction_code, uint8_t checksum) {
        return (instruction ^ checksum) == 0xff;
    }

    template<uint8_t v_index>
    static void call_instruction_processor(uint8_t instruction_id) {
        using current_instruction_t = std::tuple_element<v_index, instructions_t>;
        if (current_instruction::instruction_id == instruction_id) {
            execute_command_set<current_instruction_t>();
        } else {
            if constexpr (v_index < std::tuple_size_v<instructions_t>) {
                call_instruction_processor<v_index + 1>(instruction_id);
            } else {
                // Instruction not found, reject one.
                auto [buffer, size, terminate] = send_nack_command_t::execute();
                transceiver_t::send(buffer, size);
            }
        }
    }

    template<class t_command_set, class t_parameters, class t_buffers>
    static bool execute_command_set(t_parameters&& parameters, t_buffers&& buffers) {
        return execute_next_command<t_command_set, 0>(t_parameters&& parameters, t_buffers&& buffers);
    }

    template<class t_command, class t_parameters, class t_buffers>
    static bool execute_command(t_parameters&& parameters, t_buffers&& buffers) {
        if constexpr (t_command::is_producer || t_command::is_consumer) {
            auto [buffer, size, terminate] = std::apply(
                    t_command::execute, 
                    std::tuple_cat(
                        select_tuple(parameters, t_command::parameter_indexes),
                        select_tuple(buffers, t_command::buffer_indexes)
                    )
                );
            if constexpr (t_command::is_producer) {
                transceiver_t::send(buffer, size);
            } else if constexpr (t_command::is_consumer) {
                transceiver_t::receive(buffer, size);
            }
            return terminate;
        } else if constexpr (t_command::is_conditional) {
            bool condition = std::apply(
                command_t::execute_conditional,
                std::tuple_cat(
                    select_tuple(parameters, command_t::parameter_indexes), 
                    select_tuple(buffers, command_t::buffer_indexes)
                )
            );
            if (condition) {
                return execute_command<command_t::on_true_t>(
                    std::forward<t_parameters>(parameters),
                    std::forward<t_buffers>(buffers)
                );
            }
            return execute_command<command_t::on_false_t>(
                std::forward<t_parameters>(parameters),
                std::forward<t_buffers>(buffers)
            );
        } else if constexpr (t_command::is_set) {
            return execute_command_set<t_command, 0>(
                std::forward<t_parameters>(parameters),
                std::forward<t_buffers>(buffers)
            );
        } else {
            return false;
        }
    }

    template<class t_command_set, uint8_t v_index, class t_parameters, class t_buffers>
    static bool execute_next_command(t_parameters&& parameters, t_buffers&& buffers) {
        if constexpr (v_index < t_command_set::size) {
            using command_t = std::tuple_element_t<v_index, t_command_set::commands_t>;
            
            if (execute_command<command_t>(
                std::forward<t_parameters>(parameters),
                std::forward<t_buffers>(buffers),
            )) {
                return true;
            }
            return execute_next_command<t_command_set, v_index + 1>(
                std::forward<t_parameters>(parameters),
                std::forward<t_buffers>(buffers),
            );
        } else {
            return false;
        }
    }
};
