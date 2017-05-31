/*
** Timer.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Timer.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Wed Apr 26 03:17:28 2017 Dimitri Wyzlic
** Last update Wed Apr 26 03:17:28 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_TIMER_HPP
#define ALFRED_TIMER_HPP

#include <chrono>
#include <functional>
#include <string>
#include <unordered_map>

//TODO Multithread is Better

namespace Alfred {

    class TimerCheckpointAlreadyExist : public std::exception {
        const char *what() const throw() override { return "Checkpoint already exist.\n"; }
    };

    class Timer {
        int max;
        int precTime = -1;
        std::chrono::time_point<std::chrono::system_clock> timeStart;
        std::function<void(const std::string &)> _onTick;
        std::function<void()> _onEnd;
        std::function<bool()> _update;
        std::unordered_map<int, std::unordered_map<std::string, std::function<void()>>> _checkpoint;

    public:
        /**
         * Create a Timer from max seconds
         * @param max max seconds
         */
        explicit Timer(int max) :
                max(max),
                _update([this]() -> bool { return(updateWithoutCallback()); }) {};

        /**
         * Create a Timer from max seconds
         * @param max max seconds
         * @param _onTick Callback called each second. Signature must be std::function<void(const std::string &)> string is the time beautified
         * @param _onEnd Callback called at the end of the time
         */
        explicit Timer(int max, std::function<void(const std::string &)> _onTick, std::function<void()> _onEnd) :
                max(max),
                _onTick(_onTick),
                _onEnd(_onEnd),
                _update([this]() -> bool { return(updateWithCallback()); }) {};

        /**
         * Set max time
         * @param time
         */
        void setTime(int time) {
            max = time;
            precTime = -1;
        }

        /*
         * Start the timer
         */
        void start() {
            timeStart = std::chrono::system_clock::now();
            precTime = -1;
        }

        /*
         * Restart the timer
         */
        void restart() { start(); };

        /**
         * Update the timer
         * @return
         */
        bool update() const { return (_update()); };

        /**
         * Add a checkpoint to the timer. Raise exception if a checkpoint with this name already exist at time time
         * @param time Triggered at Time seconds
         * @param name Name of the breakpoint
         * @param func Callback in form std::function<void()>
         */
        void addCheckpoint(int time, const std::string &name, std::function<void()> func) {
            if (_onEnd != nullptr)
                _update = [this]() -> bool { return(updateWithCallbackWithCheckpoint()); };
            else
                _update = [this]() -> bool { return(updateWithoutCallbackWithCheckpoint()); };

            if (_checkpoint[time].count(name))
                throw TimerCheckpointAlreadyExist();
            _checkpoint[time][name] = func;
        }

        /**
         * Delete a checkpoint with name name.
         * @param name Name of the checkpoint
         */
        void deleteCheckpoint(const std::string &name) {
            for (auto it : _checkpoint) {
                it.second.erase(name);
                if (it.second.empty())
                    _checkpoint.erase(it.first);
            }
            defUpdateFonction();
        }

        /**
         * Delete all checkpoint with time time
         * @param time Time at wich delete all checkpoint
         */
        void deleteCheckpoint(int time) {
            _checkpoint.erase(time);
            defUpdateFonction();
        }

    private:
        /**
         * Beautify from seconde to min
         * @param sec
         * @return string in form of -> MIN:SEC like 1:42
         */
        std::string beautifySec(int sec) const
        {
            auto minute = sec / 60;
            if (minute == 0)
                return std::to_string(sec);
            auto out = std::to_string(minute);
            out += ":" + std::to_string(sec - (minute * 60));
            return out;
        }

        //All the above updateXXX function are here to prevent if branch and optimise for the CPU (avoid lot of JMP)

        /**
         * Check if time is over and return the result
         * Call _onTick or _onEnd depending of the situation
         * @return return true if time is over. false otherwise
         */
        bool updateWithCallback() {
            auto now = std::chrono::system_clock::now();
            int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();

            if (elapsed_seconds < max) {
                if (elapsed_seconds != precTime)
                {
                    precTime = elapsed_seconds;
                    _onTick(beautifySec(elapsed_seconds));
                }
            } else {
                _onEnd();
                _update = [this]() -> bool { return(nothing()); };
            }
            return elapsed_seconds > max;
        }

        /**
         * Check if time is over and return the result
        * @return return true if time is over. false otherwise
        */
        bool updateWithoutCallback() const
        {
            auto now = std::chrono::system_clock::now();
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();
            return elapsed_seconds > max;
        }

        bool updateWithoutCallbackWithCheckpoint()
        {
            auto now = std::chrono::system_clock::now();
            auto elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();
            if (precTime != elapsed_seconds)
            {
                for (auto it : _checkpoint[elapsed_seconds])
                    it.second();
                precTime = elapsed_seconds;
            }
            return elapsed_seconds > max;
        }

        bool updateWithCallbackWithCheckpoint() {
            auto now = std::chrono::system_clock::now();
            int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(now - timeStart).count();

            if (elapsed_seconds < max) {
                if (elapsed_seconds != precTime)
                {
                    precTime = elapsed_seconds;
                    _onTick(beautifySec(elapsed_seconds));
                    for (auto it : _checkpoint[elapsed_seconds])
                        it.second();
                }
            }
            else {
                _onEnd();
                _update = [this]() -> bool { return(nothing()); };
            }
            return elapsed_seconds > max;
        }

        static bool nothing() {
            return true;
        }

        inline void defUpdateFonction()
        {
            if (_checkpoint.empty())
            {
                if (_onEnd != nullptr)
                    _update = [this]() -> bool { return(updateWithCallback()); };
                else
                    _update = [this]() -> bool { return(updateWithoutCallback()); };
            }
        }
    };
}

#endif //ALFRED_TIMER_HPP