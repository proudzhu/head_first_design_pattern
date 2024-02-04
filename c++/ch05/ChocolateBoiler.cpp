#include <memory>

class ChocolateBoiler {
    public:
        static ChocolateBoiler* getInstance()
        {
            if (uniqueInstance == nullptr) {
                uniqueInstance = new ChocolateBoiler;
            }
            return uniqueInstance;
        }

        void fill(void)
        {
            if (isEmpty()) {
                empty = false;
                boiled = true;
            }
        }

        void drain(void)
        {
            if (!isEmpty() && isBoiled()) {
                empty = true;
            }
        }

        void boil(void)
        {
            if (!isEmpty() && !isBoiled()) {
                boiled = true;
            }
        }

        bool isEmpty(void)
        {
            return empty;
        }

        bool isBoiled(void)
        {
            return boiled;
        }

    private:
        ChocolateBoiler() = default;
        bool empty = true;
        bool boiled = false;
        static ChocolateBoiler* uniqueInstance;
};

inline ChocolateBoiler* ChocolateBoiler::uniqueInstance = nullptr;

int main(int argc, char **argv)
{
    auto boiler = ChocolateBoiler::getInstance();

    boiler->fill();
    boiler->boil();
    boiler->drain();

    return 0;
}