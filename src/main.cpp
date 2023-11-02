#include <memory>

#include "Core/Application.h"

int main()
{
    auto app = std::make_unique<Application>();
    app->run();

    app.release();

    return 0;
}
