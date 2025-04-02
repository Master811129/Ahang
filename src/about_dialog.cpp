#include "about_dialog.hpp"
#include <gempyre.h>
#include <string>
#include "ahang_utils.hpp"

AboutDialog::AboutDialog(const Gempyre::Ui::FileMap& f, const std::string& indexhtml, const std::string& browser):
//Gempyre::Ui(f,indexhtml,browser,""),
Gempyre::Ui(f,indexhtml,"about",600,249,Gempyre::Ui::NoResize),
donation_link(*this,"donation"),
issues_link(*this,"issues"),
licence_link(*this,"licence"),
gempyre_version_line(*this, "p", this->root())
{
    donation_link.subscribe("click", std::bind(&ahang::open_link,"http://github.com/master811129/ahang"));
    issues_link.subscribe("click", std::bind(&ahang::open_link,"http://github.com/master811129/ahang/issues"));
    licence_link.subscribe("click", std::bind(&ahang::open_link,"https://raw.githubusercontent.com/Master811129/Ahang/main/LICENSE"));
    const auto [vf,vs,vt]=Gempyre::version();
    gempyre_version_line.set_attribute("class","tiny");
    gempyre_version_line.set_html("Gempyre version: "+std::to_string(vf)+'.'+std::to_string(vs)+'.'+std::to_string(vt));
}