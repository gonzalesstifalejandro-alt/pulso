#include <catch2/catch_test_macros.hpp>
#include "alertas/gestor_alertas.hpp"
#include "http/handlers.hpp"
#include "core/metrica.hpp"

TEST_CASE("GET /alerts retorna lista vacía cuando no hay alertas") {
    // Configuración con umbrales altos
    pulso::config::UmbralesConfig umbrales;
    umbrales.cpu_max = 80.0;
    
    pulso::alertas::GestorAlertas gestor(umbrales);
    
    // Métrica normal (por debajo del umbral)
    pulso::Metrica metricas_normales;
    metricas_normales.cpu_uso_porcentaje = 30.0;

    auto res = pulso::http::handleAlerts(gestor, metricas_normales);
    REQUIRE(res == "[]");
}

TEST_CASE("GET /alerts retorna alertas activas cuando se supera el umbral") {
    // Configuración con umbrales
    pulso::config::UmbralesConfig umbrales;
    umbrales.cpu_max = 80.0;
    
    pulso::alertas::GestorAlertas gestor(umbrales);
    
    // Métrica alta (supera el umbral de 80%)
    pulso::Metrica metricas_altas;
    metricas_altas.cpu_uso_porcentaje = 95.0;

    // Evaluamos la métrica en el gestor para activar la alerta
    gestor.evaluar(metricas_altas);

    auto res = pulso::http::handleAlerts(gestor, metricas_altas);
    REQUIRE(res.find("CPU") != std::string::npos);
}