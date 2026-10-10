#include <doctest/doctest.h>
#include <httplib.h>
#include <string>

TEST_CASE("GET /alerts responde 200 y devuelve estado de alertas") {
    httplib::Client cli("http://localhost:8080");

    SUBCASE("Sin alertas activas") {
        auto res = cli.Get("/alerts");
        CHECK(res != nullptr);
        CHECK(res->status == 200);
        CHECK(res->body.find("alerts") != std::string::npos);
    }

    SUBCASE("Con alertas activas") {
        auto res = cli.Get("/alerts");
        CHECK(res != nullptr);
        CHECK(res->status == 200);
    }
}