// Project includes
#include "falltergeist/vfs/NativeDriver.h"
#include "falltergeist/vfs/NativeFile.h"

// Third party includes

// stdlib
#include <filesystem>

namespace Falltergeist::VFS {

    NativeDriver::NativeDriver(const std::filesystem::path& basePath)
        : _name("NativeDriver"), _basePath(basePath) {
    }

    const std::string& NativeDriver::name() {
        return _name;
    }

    bool NativeDriver::exists(const std::string& path) {
        std::filesystem::path fsPath = std::filesystem::absolute(_basePath) / std::filesystem::path(path);
        return std::filesystem::exists(fsPath);
    }

    std::shared_ptr<IFile> NativeDriver::open(const std::string& path, IFile::OpenMode mode) {
        std::filesystem::path fsPath = std::filesystem::absolute(_basePath) / std::filesystem::path(path);
        auto file = std::make_shared<NativeFile>(fsPath);
        file->_open(mode);
        return file;
    }
}
