/**
 * @Author: Amélie Heinrich
 * @Create Time: 2024-03-17 13:39:27
 */

#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

template<typename Resource>
class ResourceManager
{
public:
    ResourceManager(const std::string& folder, const std::string& extension)
        : _folder("res/" + folder + "/"), _extension("." + extension)
    {
    }

    const Resource& Get(const std::string& name)
    {
        if (!Exists(name)) {
            Add(name);
        }

        return *_resources.at(name).get();
    }

    bool Exists(const std::string& name) const
    {
        return _resources.find(name) != _resources.end();
    }

    void Add(const std::string& name)
    {
        std::shared_ptr<Resource> r = std::make_shared<Resource>();

        if (!r->loadFromFile(GetFullFilename(name))) {
            std::shared_ptr<Resource> fail = std::make_shared<Resource>();
            fail->loadFromFile(_folder + "_fail_" + _extension);
            _resources.insert(std::make_pair(name, fail));
        } else {
            _resources.insert(std::make_pair(name, r));
        }
    }

private:
    std::string GetFullFilename(const std::string& name)
    {
        return _folder + name + _extension;
    }

    const std::string _folder;
    const std::string _extension;
    std::unordered_map<std::string, std::shared_ptr<Resource>> _resources;
};
