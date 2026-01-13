#include <drogon/drogon.h>

int main() {
    using namespace drogon;

    // set doc root for http document 
    app().setDocumentRoot("./static");

    // index page is home page, holds basic information 
    app().registerHandler(
        "/",
        [](const HttpRequestPtr &, std::function<void(const HttpResponsePtr &)> &&callback) {
            callback(HttpResponse::newFileResponse("./static/pages/index.html"));
        },
        {Get}
    );

    app().registerHandler(
        "/blog",
        [](const HttpRequestPtr &, std::function<void(const HttpResponsePtr &)> &&callback) {
            callback(HttpResponse::newFileResponse("./static/pages/blog.html"));
        },
        {Get}
    );

    app().registerHandler(
        "/about",
        [](const HttpRequestPtr &, std::function<void(const HttpResponsePtr &)> &&callback) {
            callback(HttpResponse::newFileResponse("./static/pages/about.html"));
        },
        {Get}
    );

    app().registerHandler(
        "/resources",
        [](const HttpRequestPtr &, std::function<void(const HttpResponsePtr &)> &&callback) {
            callback(HttpResponse::newFileResponse("./static/pages/resources.html"));
        },
        {Get}
    );

    // Listen + run
    app()
        .addListener("0.0.0.0", 8080)
        .setThreadNum(2)
        .run();

    return 0;
}
