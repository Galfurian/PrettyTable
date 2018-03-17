#include <string>

namespace align
{

/// Kinds of string alignment.
enum align_t
{
    left,
    center,
    right,
};

/// @brief Helper class to center strings.
class centered
{
private:
    /// The stored string which needs to be centered.
    std::string str;

public:
    /// @brief Initialize the helper.
    explicit centered() :
        str()
    {
        // Nothing to do.
    }

    /// @brief Initialize the helper.
    explicit centered(std::string _str) :
        str(std::move(_str))
    {
        // Nothing to do.
    }

    /// @brief Centers the string.
    friend inline std::ostream & operator<<(std::ostream & left,
                                            const centered & right)
    {
        auto left_width = left.width();
        auto right_width = right.str.length();
        if (left_width > right_width)
        {
            auto left_spaces = (left_width + right_width) / 2;
            left.width(left_spaces);
            left << right.str;
            left.width(left_width - left_spaces);
            left << "";
        }
        else
        {
            left << right.str;
        }
        return left;
    }

    /// @brief Centers the string.
    inline centered & operator<<(std::string const & right)
    {
        str = right;
        return (*this);
    }
};

}
