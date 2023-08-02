#pragma once
#include <gempyre.h>
#include <string>

class AboutDialog:
public Gempyre::Ui
{
    public:
    AboutDialog(const Gempyre::Ui::Filemap& f, const std::string& indexhtml, const std::string& browser);
    Gempyre::Element donation_link;
    Gempyre::Element issues_link;
    Gempyre::Element licence_link;
    Gempyre::Element gempyre_version_line;
};