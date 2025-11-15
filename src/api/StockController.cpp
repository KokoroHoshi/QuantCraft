#include "StockController.h"

#include "../services/StockService.h"

void StockController::getTest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_INFO << "/test endpoint hit!";

    json data = {
        {"message", "HHW!"},
        {"status", "success"}
    };

    auto res = HttpResponse::newHttpResponse();
    res->setContentTypeCode(CT_APPLICATION_JSON);
    res->setBody(data.dump()); // nlohmann::json -> string

    callback(res);
}

void StockController::getStock(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    LOG_INFO << "/api/stock endpoint hit!";
    try {
        auto symbol = req->getParameter("symbol");
        auto rangeParam = req->getParameter("range");
        std::string range = rangeParam.empty()? "1y" : rangeParam;
        auto intervalParam = req->getParameter("interval");
        std::string interval = intervalParam.empty()? "1d" : intervalParam;

        auto data = StockService::fetchStock(symbol, range, interval);

        auto res = HttpResponse::newHttpResponse();
        res->setContentTypeCode(CT_APPLICATION_JSON);
        res->setBody(data.dump());

        callback(res);
    } catch (const std::exception &e) {
        auto res = HttpResponse::newHttpResponse();
        
        res->setStatusCode(k500InternalServerError);
        res->setBody(e.what());
        
        callback(res);
    }
}