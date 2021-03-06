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

#include "stringUtils.hpp"
#include "tableColumn.hpp"
#include "tableRow.hpp"

#include <sstream>
#include <map>
#include <iomanip>

/// @brief A simple formatted table.
class Table
{
public:
    enum SymbolType
    {
        HorizontalDivider,
        VerticalDivider,
        Crossings,
    };

    /// @brief Constructor.
    explicit Table() :
        columns(),
        rows(),
        marginSize(),
        symbols()
    {
        // Set the default symbols.
        this->setDefaultSymbols();
    }

    /// @brief Allows to set the margins.
    inline void setMarginSize(std::string::size_type const & s)
    {
        marginSize = s;
    }

    /// @brief Allows to set a character to use for a specific place.
    inline void setSymbol(SymbolType type, char symbol)
    {
        symbols[type] = symbol;
    }

    /// @brief Sets the default the symbols.
    inline void setDefaultSymbols()
    {
        symbols[HorizontalDivider] = '-';
        symbols[VerticalDivider] = '|';
        symbols[Crossings] = '+';
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
    inline void addRow(TableRow row)
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
                auto wrappedText =
                    StringUtils::text_wrap(cell, column_it->width);
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

    /// @brief Adds the column headers.
    inline void addColumnHeaders()
    {
        TableRow new_row;
        for (auto const & column : columns)
        {
            new_row.emplace_back(column.getTitle());
        }
        rows.emplace_back(new_row);
    }

    /// @brief Adds a divider.
    inline void addDivider()
    {
        TableRow new_row;
        new_row.divider = true;
        rows.emplace_back(new_row);
    }

    /// @brief Adds an header with the given text.
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
        auto margin = std::string(marginSize, ' ');
        auto hdiv = symbols[HorizontalDivider];
        auto vdiv = symbols[VerticalDivider];
        auto cross = symbols[Crossings];

        std::stringstream ss;
        for (auto row_it = rows.begin(); row_it != rows.end(); ++row_it)
        {
            auto row = (*row_it);
            if (row.isDivider())
            {
                ss << cross;
                if ((row_it == rows.begin()) ||
                    (std::next(row_it) == rows.end()))
                {
                    ss << std::string(
                        getTotalWidth() +
                        (columns.size() - 1) +
                        columns.size() * marginSize * 2, hdiv)
                       << cross;
                }
                else
                {
                    for (auto column : columns)
                    {
                        ss << std::string(column.width + marginSize * 2, hdiv)
                           << cross;
                    }
                }
                ss << "\n";
                continue;
            }
            if (row.isHeader())
            {
                ss << vdiv;
                ss << margin;
                ss << std::setw(this->getTotalWidth()
                                + (marginSize * 2 + 1) * (columns.size() - 1));
                ss << std::right << align::centered(row[0]);
                ss << margin;
                ss << vdiv;
                ss << "\n";
                continue;
            }
            ss << vdiv;
            for (size_t i = 0; i < row.size(); ++i)
            {
                auto const & column = columns[i];
                ss << margin;
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
                    ss << std::right << align::centered(row[i]);
                }
                ss << margin;
                ss << vdiv;
            }
            ss << "\n";
        }
        return ss.str();
    }

private:

    /// @brief Provides the total width of th table.
    /// @return The total width.
    inline int getTotalWidth() const
    {
        int totalWidth = 0;
        for (auto const & it : columns)
        {
            totalWidth += it.getWidth();
        }
        return totalWidth;
    }

    /// List of columns of the table.
    std::vector<TableColumn> columns;
    /// List of rows of the table.
    std::vector<TableRow> rows;
    /// The internal margins.
    std::string::size_type marginSize;
    /// Map of symbols;
    std::map<SymbolType, char> symbols;
};