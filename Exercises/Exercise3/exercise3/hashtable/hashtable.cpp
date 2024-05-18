
#include <string>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <>
class Hashable<int> {
    public:
    unsigned long operator()(const int& data) const noexcept {
        return (data * data);
    }
};

/* ************************************************************************** */

template <>
class Hashable<double> {
    public:
    unsigned long operator()(const double& data) const noexcept {
        long intPart = floor(data); // return the item int rounded down
        long fracPart = pow(2, 24) * (data-intPart); // function for the power - pow(base, height)
        return (intPart + fracPart);
    }
};

/* ************************************************************************** */

template <>
class Hashable<std::string> {
    public:
    unsigned long operator()(const std::string& data) const noexcept {
        unsigned long hash = 5381;
        for (unsigned long i = 0; i < data.length(); i++) {
            hash = (hash << 5) + data[i];
        }
        return hash;
    }
};

/* ************************************************************************** */

}
