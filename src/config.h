
#pragma once

#include <memory>
#include "tileset/tileset.h"

class Config {
public:
    Config();
    Config(const Config&);
    ~Config();

    static Config load(const std::string& filepath);

    int id() const;
    const std::string& name() const;
    int units() const;
    float width() const;
    float height() const;

    const std::map<std::string, assets::tileset>& tilesets() const;
    const std::map<std::string, std::pair<std::string, std::string>>& layouts() const;

protected:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};
