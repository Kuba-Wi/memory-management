#pragma once

#include <atomic>
#include <functional>

auto delete_function = [](auto* ptr) { delete ptr; };;

template <typename T>
class ControlBlock {
public:
    ControlBlock(std::function<void(T*)> del = delete_function) : deleter(del) {}
    void increaseSharedRef() { shared_refs += 1; }
    void decreaseSharedRef() { shared_refs -= 1; }
    void increaseWeakRef() { weak_refs += 1; }
    void decreaseWeakRef() { weak_refs -= 1; }
    size_t getShared() { return shared_refs; }
    size_t getWeak() { return weak_refs; }
    std::function<void(T*)>& getDeleter() { return deleter; }
    virtual ~ControlBlock() = default;

private:
    std::atomic<size_t> shared_refs = 1;
    std::atomic<size_t> weak_refs = 0;
    std::function<void(T*)> deleter;
};
