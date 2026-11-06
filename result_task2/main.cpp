#include <iostream>
#include <map>
#include <string>

class MemoryCache {
public:
    // Реализация Singleton (Мейерса) - потокобезопасна
    static MemoryCache& instance() {
        static MemoryCache inst;
        return inst;
    }

    // Запрет копирования
    MemoryCache(const MemoryCache&) = delete;
    MemoryCache& operator=(const MemoryCache&) = delete;

    void put(const std::string& key, const std::string& value) {
        if (maxSize_ > 0 && data_.size() >= static_cast<size_t>(maxSize_)
            && data_.find(key) == data_.end()) {
            std::cout << "[Cache] Limit reached (" << maxSize_
                      << "). Cannot add: " << key << "\n";
            return;
        }
        data_[key] = value;
        std::cout << "[Cache] put: " << key << " = " << value << "\n";
    }

    std::string get(const std::string& key) {
        auto it = data_.find(key);
        if (it == data_.end()) {
            std::cout << "[Cache] get: key '" << key << "' NOT FOUND\n";
            return "";
        }
        std::cout << "[Cache] get: " << key << " = " << it->second << "\n";
        return it->second;
    }

    void remove(const std::string& key) {
        data_.erase(key);
        std::cout << "[Cache] remove: " << key << "\n";
    }

    void clear() {
        data_.clear();
        std::cout << "[Cache] clear: cache is now empty\n";
    }

    size_t size() const {
        return data_.size();
    }

    bool contains(const std::string& key) const {
        bool res = data_.find(key) != data_.end();
        std::cout << "[Cache] contains('" << key << "'): " << (res ? "true" : "false") << "\n";
        return res;
    }

    void setMaxSize(int size) {
        maxSize_ = size;
        std::cout << "[Cache] setMaxSize: " << size << "\n";
    }

private:
    MemoryCache() = default;
    std::map<std::string, std::string> data_;
    int maxSize_ = 0; // 0 означает без ограничений
};

int main(int argc, char** argv) {
    // Получаем параметр из командной строки (для задания 1)
    std::string demoParam = (argc > 1) ? argv[1] : "default_value";

    std::cout << "=== MemoryCache Demo ===\n";
    std::cout << "Parameter from Docker: " << demoParam << "\n\n";

    MemoryCache& cache = MemoryCache::instance();

    cache.setMaxSize(3); // Ограничиваем кэш 3 элементами
    cache.put("name", "Davlyatshin");
    cache.put("group", "241-372");
    cache.put("subject", "TIMP");
    cache.put(demoParam, "some_value"); // Вызовет ошибку, так как лимит 3

    std::cout << "\nCurrent size: " << cache.size() << "\n";
    cache.contains("name");
    cache.contains("unknown_key");

    std::cout << "\nGetting values:\n";
    cache.get("name");
    cache.get("unknown_key");

    std::cout << "\nRemoving 'group':\n";
    cache.remove("group");
    std::cout << "Size after remove: " << cache.size() << "\n";

    std::cout << "\nClearing cache:\n";
    cache.clear();
    std::cout << "Size after clear: " << cache.size() << "\n";

    return 0;
}