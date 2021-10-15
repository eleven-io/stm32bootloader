#pragma once

#include <instructions/commands/commands.h>
#include <instructions/instruction_processor.h>



// Write memory instruction.
using write_memory_instruction_processor_t = instruction_processor_t<
    bootloader_proto_t::write_memory,
    command_set_t<
        conditional_true_command_t<
            check_rdp_is_active_t,          // Condition.
            send_nack_and_exit_command_t    // RDP is active. Send NACK and terminate instruction.
        >,
        // Go further. Receive address.
        send_ack_command_t,
        receive_data_with_cs_t<0>,
        conditional_false_command_t<
            validate_checksum_t,            // Condition.
            send_nack_and_exit_command_t    // Checksum is invalid. Send NACK and terminate instruction.
        >,
        // Go further. Receive variable size data.
        send_ack_command_t,
        receive_data_command_t<1>,
        receive_variable_size_data_with_cs_t<1, 0>,
        conditional_false_command_t<
            validate_checksum_t,            // Condition.
            send_nack_and_exit_command_t    // Checksum is invalid. Send NACK and terminate instruction.
        >,
        // Write data.
        execute_and_return_command_t<
            write_to_memory_command_t<0, 1, 0>
        >
    >,
    parameter_set_t<4, 1>,
    buffer_t<256>
>;
