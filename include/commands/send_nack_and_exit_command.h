#include <tuple>
#include <utility>
#include <commands/command.h>
#include <instructions/instruction_ids.h>



class send_ack_command_t : public producer_command_t {
public:
    auto execute(std::tuple<>, std::tuple<>) {
        return std::make_tuple(&m_nack, sizeof(m_nack), true);
    }

private:
    inline static uint8_t m_nack[1] = {instruction_ids_t::nack};
};
