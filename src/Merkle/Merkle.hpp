/*
** Merkle.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Merkle.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Thu Aug 24 15:49:53 2017 Dimitri Wyzlic
** Last update Thu Aug 24 15:49:53 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_MERKLE_HPP
#define ALFRED_MERKLE_HPP

#include <functional>
#include <vector>

namespace Alfred
{

    template <typename T>
    struct __MerkleLeaf
    {
        T _data;
        std::string _hash;
        std::vector<struct __MerkleLeaf<T> *> *_childs;
    };

    template <typename T>
    class Merkle
    {
    private:
        std::function<std::string(T)> _hash_func;
        __MerkleLeaf<T> *_root;

    public:
        explicit Merkle(const std::function<std::string(T)> &hash_func) : _hash_func(hash_func)
        {
            _root = nullptr;
        }
    }; //Class Merkle
} //Namespace Alfred

#endif //ALFRED_MERKLE_HPP
