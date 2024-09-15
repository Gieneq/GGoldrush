#pragma once

namespace gui {

    template <typename ClassType, typename... Args>
    class Callback {
    public:
        Callback(ClassType* instance, void (ClassType::*memberFunction)(Args...)) : object(instance), function(memberFunction) {}

        void execute(Args... args) {
            if (object && function) {
                function(args...);
            }
        }

    private:
        ClassType* object;
        void (ClassType::*function)(Args...);
    };
}