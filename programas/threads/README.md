# Exemplos de Theads

## Alô mundo das threads
Executar o programa `aloMundo`

## Erros conhecidos e suas soluções

1. Constante não reconhecida pelo VS-Code mas reconhecida pelo GCC

    **Sintoma**: uma constante (por exemplo CLOCK_TAI) não é reconhecida pelo VS-Code (Intellisense), mas o código compila sem problemas

    **Solução**: configurar o c_cpp_properties.json
    - Pressione Ctrl+Shift+P, digite "C/C++: Edit Configurations (JSON)".
    - No arquivo .vscode/c_cpp_properties.json gerado, adicione/atualize:
    - Ao final, salve e recarregue a janela (Ctrl+Shift+P > "Developer: Reload Window")
    ```json
    "defines": [
        "_GNU_SOURCE"  // Habilita extensões GNU
    ],
    ```
---
