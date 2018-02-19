/// @file    table.hpp
/// @brief   Define the class Table.
/// @details This class allows to hadle a printable table.
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

#include "align.hpp"

#include <vector>
#include <sstream>
#include <iomanip>

/// The structure used to provide a row.
class TableRow :
    public std::vector<std::string>
{
public:
    TableRow() :
        divider(),
        header()
    {
        // Nothing to do.
    }

    TableRow(std::vector<std::string>::size_type const & size,
             std::string const & initializer) :
        std::vector<std::string>(size, initializer),
        divider(),
        header()
    {
        // Nothing to do.
    }

    TableRow(std::initializer_list<std::string> const & initializer) :
        std::vector<std::string>(initializer),
        divider(),
        header()
    {
        // Nothing to do.
    }

    virtual inline bool isDivider() const
    {
        return divider;
    }

    virtual inline bool isHeader() const
    {
        return header;
    }

private:
    bool divider;
    bool header;

    friend class Table;
};

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
    ///
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
            this->adjust(title);
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

/// @brief A simple formatted table.
class Table
{
public:
    /// @brief Constructor.
    Table() = default;

    /// @brief Constructor.
    /// @param _title The title of the table.
    explicit Table(std::string _title) :
        title(std::move(_title)),
        columns(),
        rows()
    {
        // Nothing to do.
    }

    /// @brief Allows to add a column.
    /// @param columnTitle     The column title.
    /// @param columnAlignment The column alignment.
    /// @param columnWidth     The column width.
    inline void addColumn(TableColumn column)
    {
        columns.emplace_back(column);
    }

    /// @brief Allows to add a row of values.
    /// @param row The vector which containts the row values.
    inline void pushRow(TableRow row)
    {
        if (row.size() != columns.size())
        {
            return;
        }
        std::vector<TableRow> new_rows;
        new_rows.emplace_back(row);

        auto row_it = 0;
        auto column_it = columns.begin();
        for (; row_it < row.size(); ++row_it, ++column_it)
        {
            auto cell = row[row_it];

            if (column_it->autoAdjust)
            {
                column_it->adjust(cell);
            }
            else if (cell.size() > column_it->width)
            {
                auto wrappedText = this->textWrap(cell, column_it->width);
                if (wrappedText.size() > new_rows.size())
                {
                    new_rows.resize(wrappedText.size(),
                                    TableRow(row.size(), ""));
                }
                size_t index = 0;
                for (auto const & wrappedLine : wrappedText)
                {
                    new_rows[index++][row_it] = wrappedLine;
                }
            }
        }
        for (auto & new_row : new_rows)
        {
            rows.emplace_back(new_row);
        }
    }

    inline void addDivider()
    {
        TableRow new_row;
        new_row.divider = true;
        rows.emplace_back(new_row);
    }

    inline void addHeader(std::string header)
    {
        TableRow new_row;
        new_row.header = true;
        new_row.emplace_back(header);
        rows.emplace_back(new_row);
    }

    /// @brief Removes the last row.
    inline void popRow()
    {
        rows.pop_back();
    }

    /// @brief Provides the table.
    /// @param withoutHeaders Allows to hide the header of the columns.
    /// @return The table.
    std::string getTable()
    {
        std::stringstream ss;
        for (auto const & row : rows)
        {
            if (row.isDivider())
            {
                ss << "#";
                for (auto const & column : columns)
                {
                    ss << std::string(column.width, '-');
                    ss << "#";
                }
                ss << "\n";
                continue;
            }
            if (row.isHeader())
            {
                ss << "#";
                ss << std::setw(this->getTotalWidth() + columns.size() - 1);
                ss << std::right << align::centtered(row[0]);
                ss << "#";
                ss << "\n";
                continue;
            }
            ss << "#";
            for (size_t i = 0; i < row.size(); ++i)
            {
                auto const & column = columns[i];
                ss << std::setw(column.width);
                if (column.alignment == align::left)
                {
                    ss << std::left << row[i];
                }
                else if (column.alignment == align::right)
                {
                    ss << std::right << row[i];
                }
                else
                {
                    ss << std::right << align::centtered(row[i]);
                }
                ss << "#";
            }
            ss << "\n";
        }
        return ss.str();
    }

    std::vector<std::string> textWrap(std::string const & in,
                                      std::string::size_type const & width)
    {
        auto words = this->splitString(in, " ");
        std::vector<std::string> out;
        std::string tmp;
        for (auto it = words.begin(); it != words.end(); ++it)
        {
            auto word = (*it);
            if ((tmp.size() + word.size()) > width)
            {
                out.emplace_back(tmp);
                tmp.clear();
            }
            tmp += word;
            if ((std::next(it) != words.end()) &&
                (tmp.size() < width))
            {
                tmp.push_back(' ');
            }
        }
        if (!tmp.empty())
        {
            out.emplace_back(tmp);
        }
        return out;
    }

private:

    /// @brief Provides the total width of th table.
    /// @return The total width.
    inline size_t getTotalWidth() const
    {
        size_t totalWidth = 0;
        for (auto const & it : columns)
        {
            totalWidth += it.getWidth();
        }
        return totalWidth;
    }

    std::vector<std::string> splitString(
        const std::string & source,
        const std::string & delimiter)
    {
        std::vector<std::string> result;
        size_t pos = 0;
        std::string tmp = source;
        while ((pos = tmp.find(delimiter)) != std::string::npos)
        {
            result.push_back(tmp.substr(0, pos));
            tmp.erase(0, pos + delimiter.length());
        }
        if (!tmp.empty())
        {
            result.push_back(tmp);
        }
        return result;
    }

    /// Title of the table.
    std::string title;
    /// List of columns of the table.
    std::vector<TableColumn> columns;
    /// List of rows of the table.
    std::vector<TableRow> rows;
};
