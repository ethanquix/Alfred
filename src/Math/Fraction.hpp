/*
** Fraction.hpp for Alfred in /home/wyzlic_a/delivery/Alfred/Fraction.hpp
**
** Made by Dimitri Wyzlic
** Login   <dimitri1.wyzlic@epitech.eu>
**
** Started on  Tue Sep 05 15:03:54 2017 Dimitri Wyzlic
** Last update Tue Sep 05 15:03:54 2017 Dimitri Wyzlic
*/

#ifndef ALFRED_FRACTION_HPP
#define ALFRED_FRACTION_HPP

#include <ostream>

namespace Alfred
{
    template <typename N, typename D>
    class Fraction
    {
    private:
        N _numerator;
        D _denominator;
    public:
        Fraction(N numerator, D denominator) :
            _numerator(numerator),
            _denominator(denominator)
        {}

        N getNumerator() const
        { return _numerator; }

        D getDenominator() const
        { return _denominator; }

        explicit operator int() const
        { return static_cast<int>(_numerator) / static_cast<int>(_denominator); }

        explicit operator float() const
        { return static_cast<float>(_numerator) / static_cast<float>(_denominator); }

        explicit operator double() const
        { return static_cast<double>(_numerator) / static_cast<double>(_denominator); }

        friend std::ostream &operator<<(std::ostream &os, const Fraction &fraction)
        {
            os << fraction._numerator << " / " << fraction._denominator << std::endl;
            return os;
        }

        template <typename X>
        Fraction<X, D> &setNumerator(const X &newNumerator)
        { return *new Fraction<X, D>(newNumerator, _denominator); }

        template <typename X>
        Fraction<N, X> &setDenominator(const X &newDenominator)
        { return *new Fraction<X, D>(_numerator, newDenominator); }
    };

    template <typename N, typename D>
    Fraction<N, D> &MakeFraction(N _num, D _den)
    { return *new Fraction<N, D>(_num, _den); };
}

#endif //ALFRED_FRACTION_HPP
