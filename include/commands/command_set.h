#include <tuple>


template<class... t_commands>
class command_set_t {
    using commands_t = std::tuple<t_commands>;
    constexpr static std::size_t size = std::tuple_size_v<commands_t>;
};
