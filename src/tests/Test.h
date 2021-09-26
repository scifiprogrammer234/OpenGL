#pragma once

namespace test {

    class Test {
    public:
        Test() {}
        virtual ~Test() {} // virtual destructor

        virtual void onUpdate(float deltaTime) {}
        virtual void onRender() {}
        virtual void onImGuiRender() {}
    };

}