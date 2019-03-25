#include "config.h"
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include "tileset/tileset.h"

#include <iostream>
#include <boost/filesystem.hpp>


struct Config::Impl {
    std::map<std::string, assets::tileset> _tilesets;
};

Config::Config() : pImpl(std::make_unique<Impl>()) {}

Config::Config(const Config& other) : pImpl(std::make_unique<Impl>(*other.pImpl)) {
    pImpl->_tilesets = other.pImpl->_tilesets;
}

Config::~Config() {}

Config Config::load(const std::string& filepath) {
    rapidxml::file<> xmlFile(filepath.c_str());
    rapidxml::xml_document<> doc;
    try {
        Config config;
        auto basepath = boost::filesystem::path(filepath).parent_path();

        doc.parse<0>(xmlFile.data());
        auto root = doc.first_node();

        // Parse tilesets
        auto tilesets = root->first_node("tilesets");
        auto tileset_node = tilesets->first_node("tileset");
        while (tileset_node) {
            auto filename = (basepath / tileset_node->value()).normalize().generic_string();
            auto [_, inserted] = config.pImpl->_tilesets.try_emplace(tileset_node->first_attribute("id")->value(), assets::tileset::load("filename"));
        }
        return config;
    }
    catch(rapidxml::parse_error & e) {
        std::cerr << "Parse error: " << e.what() << std::endl << "At: " << e.where<char>() << std::endl;
        throw std::runtime_error("Invalid file"); // TODO
    }
    catch(std::exception& e) {
        // TODO:
        throw e;
    }
}
