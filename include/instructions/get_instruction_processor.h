#pragma once

#include <instructions/commands/commands.h>
#include <instructions/instruction_processor.h>



// Get instruction.
using get_instruction_processor_t = instruction_processor_t<
    instruiction_ids_t::get,
    command_set_t<
        send_ack_command_t,
        get_command_t,
        send_ack_command_t
    >
>;
