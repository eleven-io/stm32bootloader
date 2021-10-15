#pragma once

#include <instructions/commands/commands.h>
#include <instructions/instruction_processor.h>



// Read memory instruction.
using read_memory_instruction_processor_t = instruction_processor_t<
    bootloader_proto_t::read_memory,
    command_set_t<
        conditional_true_command_t<
            check_rdp_is_active_t,          // Condition.
            send_nack_and_exit_command_t    // RDP is active. Send NACK and terminate instruction.
        >,
        // Go further. Receive address.
        send_ack_command_t,
        conditional_false_command_t<
            receive_and_validate_read_address_t<0>, // Condition.
            send_nack_and_exit_command_t            // Checksum is invalid. Send NACK and terminate instruction.
        >,
        // Go further. Receive data length.
        send_ack_command_t,
        conditional_false_command_t<
            receive_data_and_validate_length_t<0, 1>,   // Condition.
            send_nack_and_exit_command_t                // Checksum is invalid. Send NACK and terminate instruction.
        >,
        // Go further. Send data.
        send_ack_command_t,
        build_read_data_result_t<0, 1>
    >,
    send_data_t<4, 1>
>;
