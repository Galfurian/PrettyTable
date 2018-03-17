/// @file    tableColumn.hpp
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

#include "utils/align.hpp"

#include <string>

/// @brief A class which provide access and means to manage a table column.
class TableColumn
{
public:
    /// Column Title.
    std::string title;
    /// Column alignment.
    align::align_t alignment;
    /// Column width.
    std::string::size_type width;
    /// If the column needs to autoadjust to the lenght of the content.
    const bool autoAdjust;

    /// @brief Constructor.
    /// @param _title     The column title.
    /// @param _alignment The column alignment.
    /// @param _width     The column width.
    TableColumn(std::string _title,
                align::align_t _alignment,
                std::string::size_type _width,
                const bool _autoAdjust) :
        title(std::move(_title)),
        alignment(_alignment),
        width(_width),
        autoAdjust(_autoAdjust)
    {
        if (autoAdjust)
        {
            adjust(title);
        }
    }

    /// @brief Provide access to the title of the column.
    /// @return The title of the column
    inline std::string getTitle() const
    {
        return title;
    }

    /// @brief Provides the width of the column.
    /// @return The width of the column.
    inline std::string::size_type getWidth() const
    {
        return width;
    }

    /// @brief Provides access to the allignment of the column.
    /// @return The allignment of the column.
    inline align::align_t getAlignment()
    {
        return alignment;
    }

    inline void adjust(std::string const & reference)
    {
        if (autoAdjust)
        {
            auto _width = reference.size();
            if (_width > width) width = _width;
        }
    }
};
