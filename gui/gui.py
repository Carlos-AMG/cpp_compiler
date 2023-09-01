
import lexer_module


lex1 = lexer_module.Lexer()
line = "123 + 1"
lex1.analyze(line)
for token in lex1.tokens:
    print(f"Token: {token.name}, value: {token.value}")

# tok = lexer_module.Token("hola", "askldjfaklsj")