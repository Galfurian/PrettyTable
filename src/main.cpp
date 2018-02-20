#include <iostream>
#include "table.hpp"

int main(int argc, char ** argv)
{
    Table table;
    table.setMarginSize(0);
    table.setSymbol(Table::VerticalDivider, '|');
    table.setSymbol(Table::HorizontalDivider, '-');
    table.setSymbol(Table::Crossings, '+');
    table.addColumn(TableColumn("Name", align::center, 0, true));
    table.addColumn(TableColumn("Age", align::center, 0, false));
    table.addColumn(TableColumn("Description", align::center, 0, false));
    table.addDivider();
    table.addHeader("Header 1");
    table.addDivider();
    table.addColumnHeaders();
    table.addDivider();
    table.addRow({"Jhon",
                  "12",
                  "On the other hand, we denounce with righteous indignation and dislike men who are so beguiled and demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee the pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty through weakness of will, which is the same as saying through shrinking from toil and pain. These cases are perfectly simple and easy to distinguish. In a free hour, when our power of choice is untrammeled and when nothing prevents our being able to do what we like best, every pleasure is to be welcomed and every pain avoided. But in certain circumstances and owing to the claims of duty or the obligations of business it will frequently occur that pleasures have to be repudiated and annoyances accepted. The wise man therefore always holds in these matters to this principle of selection: he rejects pleasures to secure other greater pleasures, or else he endures pains to avoid worse pains."});
    table.addDivider();
    table.addHeader("Header 2");
    table.addDivider();
    table.addRow({"Tabita",
                  "24",
                  "At vero eos et accusamus et iusto odio dignissimos ducimus, qui blanditiis praesentium voluptatum deleniti atque corrupti, quos dolores et quas molestias excepturi sint, obcaecati cupiditate non provident, similique sunt in culpa, qui officia deserunt mollitia animi, id est laborum et dolorum fuga. Et harum quidem rerum facilis est et expedita distinctio. Nam libero tempore, cum soluta nobis est eligendi optio, cumque nihil impedit, quo minus id, quod maxime placeat, facere possimus, omnis voluptas assumenda est, omnis dolor repellendus. Temporibus autem quibusdam et aut officiis debitis aut rerum necessitatibus saepe eveniet, ut et voluptates repudiandae sint et molestiae non recusandae. Itaque earum rerum hic tenetur a sapiente delectus, ut aut reiciendis voluptatibus maiores alias consequatur aut perferendis doloribus asperiores repellat"});
    table.addDivider();
    std::cout << table.getTable();
    std::cout << "Done";
    return 0;
}