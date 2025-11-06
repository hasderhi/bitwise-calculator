#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char expr[256];

    printf("Enter expression> ");
    if (!fgets(expr, sizeof(expr), stdin)) return 1;

    expr[strcspn(expr, "\n")] = 0;

    FILE *f = fopen("temp_eval.c", "w");
    if (!f) {
        perror("fopen");
        return 1;
    }

    fprintf(f,
        "#include <stdio.h>\n"
        "int main(){\n"
        "    unsigned long long result = %s;\n"
        "    printf(\"%%llu\\n\", result);\n"
        "    return 0;\n"
        "}\n", expr);
    fclose(f);

    system("gcc temp_eval.c -o temp_eval.exe >nul 2>nul");
    printf("Result: ");
    system("temp_eval.exe");

    remove("temp_eval.c");
    remove("temp_eval.exe");

    return 0;
}
