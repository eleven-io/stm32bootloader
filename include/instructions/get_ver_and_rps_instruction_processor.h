#pragma once

#include <instructions/commands/commands.h>
#include <instructions/instruction_processor.h>



// Get bootloader version and read protection status instruction.
using get_ver_and_rps_instruction_processor_t = instruction_processor_t<
    bootloader_proto_t::get_ver_and_rps,
    command_set_t<
        send_ack_command_t,
        get_ver_and_rps_command_t,
        send_ack_command_t
    >
>;
