#include "config.h"

#include <iostream>

#include <boost/filesystem.hpp>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>


struct Config::Impl {
    int id;
    std::string name;
    int units;
    float width, height;
    std::map<std::string, assets::tileset> _tilesets;
    std::map<std::string, std::string> _layouts;
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

        // Parse some metadata
        config.pImpl->id = atoi(root->first_attribute("id")->value());
        config.pImpl->name = root->first_attribute("name")->value();

        auto size_node = root->first_node("size");
        config.pImpl->units = atof(size_node->first_attribute("units")->value());
        config.pImpl->width = atof(size_node->first_attribute("width")->value());
        config.pImpl->height = atof(size_node->first_attribute("height")->value());

        // Parse tilesets
        auto tilesets = root->first_node("tilesets");
        auto tileset_node = tilesets->first_node("tileset");
        while (tileset_node) {
            auto filename = (basepath / tileset_node->value()).normalize().generic_string();
            auto [_, inserted] = config.pImpl->_tilesets.try_emplace(tileset_node->first_attribute("id")->value(), assets::tileset::load(filename));
            tileset_node = tileset_node->next_sibling("tileset");
        }

        // Parser layouts
        auto layouts = root->first_node("layouts");
        auto layout_node = layouts->first_node("layout");
        while (layout_node) {
            auto filename = (basepath / layout_node->value()).normalize().generic_string();
            auto [_, inserted] = config.pImpl->_layouts.try_emplace(layout_node->first_attribute("id")->value(), filename);
            layout_node = layout_node->next_sibling("layout");
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

int Config::id() const {
    return pImpl->id;
}

const std::string& Config::name() const {
    return pImpl->name;
}

int Config::units() const {
    return pImpl->units;
}

float Config::width() const {
    return pImpl->width;
}

float Config::height() const {
    return pImpl->height;
}

const std::map<std::string, assets::tileset>& Config::tilesets() const {
    return pImpl->_tilesets;
}

const std::map<std::string, std::string>& Config::layouts() const {
    return pImpl->_layouts;
}
