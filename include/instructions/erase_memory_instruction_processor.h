#pragma once

#include <instructions/commands/commands.h>
#include <instructions/instruction_processor.h>



// Erase memory instruction.
using erase_memory_instruction_processor_t = instruction_processor_t<
    bootloader_proto_t::erase_memory,
    command_set_t<
        conditional_true_command_t<
            check_rdp_is_active_t,          // Condition.
            send_nack_and_exit_command_t    // RDP is active. Send NACK and terminate instruction.
        >,
        // Go further. Receive number of pages to be erased.
        send_ack_command_t,
        receive_data_t<0>,
        conditional_command_t<
            variable_is_equal_command_t<0, 0xff>,   // Condition.
            // Execute mass erase.
            command_set_t<
                receive_data_command_t<0>,
                // Return if checksum is invalid.
                conditional_false_command_t<
                    variable_is_equal_command_t<0, 0x00>,
                    send_nack_and_exit_command_t
                >,
                execute_and_return_command_t<
                    mass_erase_command_t
                >
            >,
            // Execute paged erase.
            command_set_t<
                receive_variable_data_command_t<0, 0>,
                receive_data_command_t<1>
                conditional_false_command_t<
                    validate_erase_pages_cs_command_t<0, 1, 0>,
                    send_nack_and_exit_command_t
                >,
                execute_and_return_command_t<
                    erase_pages_command_t<0, 0>
                >
            >
        >
    >,
    parameter_set_t<1, 1>,
    buffer_t<256>
>;
