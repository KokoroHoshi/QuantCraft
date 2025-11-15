#include <drogon/drogon.h>

int main() {
    LOG_DEBUG << "Config loaded";
    drogon::app().loadConfigFile("./drogon_config.json");

    drogon::app().run();
}