#include <drogon/drogon.h>

int main() {
    drogon::app().loadConfigFile("./drogon_config.json");

    drogon::app().run();
}