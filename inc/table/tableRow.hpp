/// @file    tableRow.hpp
/// @author  Enrico Fraccaroli
/// @date    Dec 15 2015
/// @copyright
/// Copyright (c) 2015, 2016 Enrico Fraccaroli <enrico.fraccaroli@gmail.com>
/// Permission to use, copy, modify, and distribute this software for any
/// purpose with or without fee is hereby granted, provided that the above
/// copyright notice and this permission notice appear in all copies.
///
/// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
/// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
/// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
/// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
/// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
/// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
/// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#pragma once

#include <string>
#include <vector>

/// @brief Structure used to manage a row of the table.
class TableRow :
    public std::vector<std::string>
{
public:

    /// @brief Constructor.
    TableRow() :
        divider(),
        header()
    {
        // Nothing to do.
    }

    /// @brief Constructor.
    TableRow(std::vector<std::string>::size_type const & size,
             std::string const & initializer) :
        std::vector<std::string>(size, initializer),
        divider(),
        header()
    {
        // Nothing to do.
    }

    /// @brief Constructor.
    TableRow(std::initializer_list<std::string> const & initializer) :
        std::vector<std::string>(initializer),
        divider(),
        header()
    {
        // Nothing to do.
    }

    /// @brief Returns if the row is a divider.
    inline bool isDivider() const
    {
        return divider;
    }

    /// @brief Returns if the row is a header.
    inline bool isHeader() const
    {
        return header;
    }

private:
    /// The row is a divider.
    bool divider;
    /// The row is a header.
    bool header;
    friend class Table;
};
