#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Token.h"
#include "Lexer.h"

namespace py = pybind11;
constexpr auto byref = py::return_value_policy::reference_internal;

//bindings para mapear objetos (Lexer/Token a objetos de python)
// lo que hace es mapear objetos de c++ a python como un modulo de python para que podamos hacer uso de ellos desde python
// en este caso mapeamos tanto el Token como el Lexer
PYBIND11_MODULE(lexer_module, m) {
    py::class_<Lexer>(m, "Lexer")
        // .def(py::init<>()) // Not useful but we could add init params
        .def(py::init<>())
        .def("analyze", &Lexer::analyze)
        .def("getTokens", &Lexer::getTokens)
        .def_readwrite("tokens", &Lexer::tokens);
    
    py::class_<Token>(m, "Token")
        .def(py::init<std::string, std::string>())
        .def("get_token", &Token::getToken)
        .def_readwrite("name", &Token::name)
        .def_readwrite("value", &Token::value);
}