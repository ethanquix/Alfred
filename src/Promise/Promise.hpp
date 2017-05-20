#include <functional>
#include <future>

namespace Alfred
{
    template <typename RET, typename VAL>
    class Promise
    {
    private:
        Promise<RET, VAL> *child = nullptr;
        RET lastRet;
        std::function<RET(VAL)> fun;
        std::future<RET> future;
        bool hasBeenResolved = false;
    public:
        std::promise<VAL> p;

    public:
        explicit Promise(std::function<RET(VAL)> fun) :
            fun(fun)
        {
            future = std::async(std::launch::async, [&]() -> RET { this->doWork(); });
        }

        explicit Promise(std::function<RET(VAL)> fun, Promise *dad) :
            fun(fun)
        {
            future = std::async(std::launch::async, [&, dad]() -> RET { doThenWork(dad); });
        }

        Promise &then(std::function<RET(VAL)> fun)
        {
            auto tmp = this;
            while (tmp->child != nullptr)
                tmp = tmp->child;
            tmp->child = new Promise<RET, VAL>(fun, tmp);
            return *this;
        }

        RET doWork()
        {
            lastRet = fun({});
            return lastRet;
        }

        RET doThenWork(Promise *dad)
        {
            VAL arg = dad->p.get_future().get();
            lastRet = fun(arg);
            p.set_value(lastRet);
            return lastRet;
        }

        Promise &resolve(VAL arg)
        {
            if (hasBeenResolved)
                exit(666); //TODO custom exception
            hasBeenResolved = true;

            p.set_value(arg);
            return *this;
        }
    };
}