// serverTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "E:/Porjects/libhv/libhv/win64/include/hv/HttpServer.h"
using namespace hv;

int main() {
    HttpService router;
    router.GET("/ping", [](HttpRequest* req, HttpResponse* resp) {
        return resp->String("pong");
        });

    router.GET("/data", [](HttpRequest* req, HttpResponse* resp) {
        static char data[] = "0123456789";
        return resp->Data(data, 10);
        });

    router.GET("/paths", [&router](HttpRequest* req, HttpResponse* resp) {
        return resp->Json(router.Paths());
        });

    router.POST("/echo", [](const HttpContextPtr& ctx) {
        return ctx->send(ctx->body(), ctx->type());
        });

    router.GET("/", [&router](const HttpRequest* req, HttpResponse* resp) {
        std::cout << time << "new require";
        static char data[] = "test";
        return resp->Json(router.Paths());;
        });

    http_server_t server;
    server.port = 8080;
    server.service = &router;
    http_server_run(&server);
    return 0;
}