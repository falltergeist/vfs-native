#pragma once

// Project includes

// Third party includes
#include "falltergeist/vfs/IDriver.h"
#include "falltergeist/vfs/IFile.h"

// stdlib
#include <filesystem>

namespace Falltergeist::VFS {
    /**
     * NativeDriver provides support for accessing real file system path
     * It will search files relative to given basePath
     */
    class NativeDriver final : public IDriver {
    public:
        NativeDriver(const std::filesystem::path& basePath);

        ~NativeDriver() override = default;

        const std::string& name() override;

        bool exists(const std::string& path) override;

        std::shared_ptr<IFile> open(const std::string& path, IFile::OpenMode mode) override;

    private:
        std::string _name;

        std::filesystem::path _basePath;
    };
}
