

struct producer_command_t {
    constexpr static bool is_producer = true;
    constexpr static bool is_consumer = false;
    constexpr static bool is_conditional = false;
    constexpr static bool is_set = false;
};


struct consumer_command_t {
    constexpr static bool is_producer = false;
    constexpr static bool is_consumer = true;
    constexpr static bool is_conditional = false;
    constexpr static bool is_set = false;
};


struct conditional_command_t {
    constexpr static bool is_producer = false;
    constexpr static bool is_consumer = false;
    constexpr static bool is_conditional = true;
    constexpr static bool is_set = false;
};


struct command_set_command_t {
    constexpr static bool is_producer = false;
    constexpr static bool is_consumer = false;
    constexpr static bool is_conditional = false;
    constexpr static bool is_set = true;
};