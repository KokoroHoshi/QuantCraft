#ifndef STOCKCONTROLLER_H
#define STOCKCONTROLLER_H

#include <drogon/HttpController.h>

using namespace drogon;

class StockController : public HttpController<StockController> {
public:
    METHOD_LIST_BEGIN
    // GET /test
    ADD_METHOD_TO(StockController::getTest, "/test", Get);

    // GET /api/stock?symbol=0050.TW&range=1y&interval=1d
    ADD_METHOD_TO(StockController::getStock, "/api/stock", Get);
    METHOD_LIST_END

    void getTest(const HttpRequestPtr &req,
                 std::function<void(const HttpResponsePtr &)> &&callback);

    void getStock(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback
    );
};

#endif