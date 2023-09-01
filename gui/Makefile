lexer_module: ../backend/Lexer.cpp ../backend/Token.cpp ../backend/utils/utils.cpp ../backend/lexer_bindings.cpp
	c++ -O3 -Wall -shared -std=c++11 -fPIC `python3 -m pybind11 --includes` \
	../backend/Lexer.cpp ../backend/Token.cpp ../backend/utils/utils.cpp \
	../backend/lexer_bindings.cpp -o lexer_module`python3-config --extension-suffix`