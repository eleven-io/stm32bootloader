#pragma once

#include <instructions/commands/commands.h>
#include <instructions/instruction_processor.h>



// Go instruction.
using go_instruction_processor_t = instruction_processor_t<
    bootloader_proto_t::go,
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
        // Go further. Go to the specified address.
        send_ack_command_t,
        go_to_address_command_t<0>
    >,
    parameter_set_t<4>
>;
