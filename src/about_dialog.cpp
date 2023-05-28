#include "about_dialog.hpp"
#include <gempyre.h>
#include "ahang_utils.hpp"

AboutDialog::AboutDialog(const Gempyre::Ui::Filemap& f, const std::string& indexhtml, const std::string& browser):
Gempyre::Ui(f,indexhtml,browser,""),
donation_link(*this,"donation"),
issues_link(*this,"issues"),
licence_link(*this,"licence")
{
    donation_link.subscribe("click", std::bind(&ahang::open_link,"http://github.com/master811129/ahang"));
    issues_link.subscribe("click", std::bind(&ahang::open_link,"http://github.com/master811129/ahang/issues"));
    licence_link.subscribe("click", std::bind(&ahang::open_link,"https://raw.githubusercontent.com/Master811129/Ahang/main/LICENSE"));
}