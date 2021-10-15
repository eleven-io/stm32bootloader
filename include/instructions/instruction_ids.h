#include <cstdint>



struct instruiction_ids_t {
    // Acquisition flags.
    constexpr static uint8_t ack = 0x79;
    constexpr static uint8_t nack = 0x1f;

    // Instructions.
    constexpr static uint8_t get = 0x00;
    constexpr static uint8_t get_ver_and_rps = 0x01;
    constexpr static uint8_t get_id = 0x02;
    constexpr static uint8_t read_memory = 0x11;
    constexpr static uint8_t go = 0x21;
    constexpr static uint8_t write_memory = 0x31;
    constexpr static uint8_t erase_memory = 0x43;
    constexpr static uint8_t extended_erase_memory = 0x44;
    constexpr static uint8_t write_protect = 0x63;
    constexpr static uint8_t write_unprotect = 0x73;
    constexpr static uint8_t readout_protect = 0x82;
    constexpr static uint8_t readout_unprotect = 0x92;
    constexpr static uint8_t get_checksum = 0xa1;
};
