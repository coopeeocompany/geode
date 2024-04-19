#include <loader/LoaderImpl.hpp>

#include <Geode/loader/Dirs.hpp>
#include <Geode/loader/Loader.hpp>
#include <Geode/loader/Log.hpp>
#include <loader/ModImpl.hpp>
#include <loader/IPC.hpp>
#include <loader/console.hpp>
#include <iostream>
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>

#include <loader/LogImpl.hpp>

using namespace geode::prelude;

bool s_isOpen = false;

void console::messageBox(char const* title, std::string const& info, Severity) {
    std::cout << title << ": " << info << std::endl;
}

void console::log(std::string const& msg, Severity severity) {
    if (s_isOpen) {
        int colorcode = 0;
        switch (severity) {
            case Severity::Debug: colorcode = 36; break;
            case Severity::Info: colorcode = 34; break;
            case Severity::Warning: colorcode = 33; break;
            case Severity::Error: colorcode = 31; break;
            default: colorcode = 35; break;
        }
        auto newMsg = "\033[1;" + std::to_string(colorcode) + "m" + msg.substr(0, 8) + "\033[0m" + msg.substr(8);

        std::cout << newMsg << "\n" << std::flush;
    }
}

void console::openIfClosed() {
    if (s_isOpen) return;

    std::filesystem::path(getpwuid(getuid())->pw_dir);
    freopen(std::filesystem::path(dirs::getGeodeDir() / "geode_log.txt").string().c_str(), "w", stdout);
    s_isOpen = true;
}

void console::setup() {}

// void Loader::Impl::postIPCReply(
//     void* rawPipeHandle, std::string const& replyID, matjson::Value const& data
// ) {}

void geode::ipc::setup() {
    #warning "Set up pipes or smth for this platform"
    log::warn("IPC is not supported on this platform");
}

bool Loader::Impl::userTriedToLoadDLLs() const {
    return false;
}

bool Loader::Impl::supportsLaunchArguments() const {
    return false;
}

std::string Loader::Impl::getLaunchCommand() const {
    return std::string(); // Empty
}

void Loader::Impl::addNativeBinariesPath(ghc::filesystem::path const& path) {
    log::warn("LoaderImpl::addNativeBinariesPath not implement on this platform, not adding path {}", path.string());
}

std::string Loader::Impl::getGameVersion() {
    NSBundle* mainBundle = [NSBundle mainBundle];
    NSDictionary* infoDictionary = [mainBundle infoDictionary];

    NSString *version = infoDictionary[@"CFBundleShortVersionString"];

    return std::string([version UTF8String]);
}