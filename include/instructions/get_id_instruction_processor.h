#pragma once

#include <instructions/commands/commands.h>
#include <instructions/instruction_processor.h>



// Get ID command.
using get_id_instruction_processor_t = instruction_processor_t<
    bootloader_proto_t::get_id,
    command_set_t<
        send_ack_command_t,
        send_constant_data_command_t<build_cid_result_t>,
        send_ack_command_t
    >
>;
