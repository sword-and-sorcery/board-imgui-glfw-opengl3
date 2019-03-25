
#pragma once

#include <memory>

class Config {
public:
    Config();
    Config(const Config&);
    ~Config();

    static Config load(const std::string& filepath);

protected:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};
