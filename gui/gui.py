import tkinter as tk
import  lexer_module

lex1 = lexer_module.Lexer()

# funcion que recibe un texto desde la gui y se lo manda a procesasar a la funcion de analyze del lexer
# una vez el analisis lexico termina, imprimimos en la gui los tokens que hemos encontrado en la cadena
def lexer():
    output_textbox.delete("1.0", "end")
    lex1 = lexer_module.Lexer()
    input_text = input_textbox.get("1.0", "end-1c")
    lex1.analyze(input_text)
    output_textbox.delete("1.0", "end")
    for token in lex1.tokens:
        output_textbox.insert("end", f"Token: {token.name}, value: {token.value}\n")

# funcion para limpiar tanto la entrada de datos como la salida de datos
def clear_textboxes():
    input_textbox.delete("1.0", "end")
    output_textbox.delete("1.0", "end")

# Create the main window
root = tk.Tk()
root.title("Lexer")

# Create the input textbox on the left
input_textbox = tk.Text(root, width=40, height=10)
input_textbox.grid(row=0, column=0, padx=10, pady=10)

# Create the button in the middle
lexer_button = tk.Button(root, text="Tokenize", command=lexer) #
lexer_button.grid(row=1, column=0, padx=10, pady=5)

# Create the clear button below the lexer button
clear_button = tk.Button(root, text="Clear", command=clear_textboxes)
clear_button.grid(row=2, column=0, padx=10, pady=5)

# Create the output textbox on the right
output_textbox = tk.Text(root, width=40, height=10)
output_textbox.grid(row=0, column=1, padx=10, pady=10)

# Start the Tkinter main loop
root.mainloop()
